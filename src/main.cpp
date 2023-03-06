#include <Arduino.h>
#include <WiFi.h>
#include "SPIFFS.h"

#include "control_point_prefs.h"
#include "registration_server.h"
#include "initial_server.h"
#include "control_point_server.h"
#include "esp_now_handler.h"
#include "api_wrapper.h"

const String version = "0.1.1";
AsyncWebServer server(80);

unsigned long restartInterval = 86400000;
unsigned long previousMillis = 0;
unsigned long interval = 30000;
bool isConnected = false;
bool hasPreferences = false;
String macAddress;

void connectToWifi(const char *ssid, const char *key){
  WiFi.mode(WIFI_AP_STA);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(getName().c_str());
  Serial.println("connecting");
  WiFi.begin(ssid, key);
  int c = 0;

  while(c < 20){
    if(WiFi.status() == WL_CONNECTED){
      Serial.println("connected");
      IPAddress ip = WiFi.localIP();
      Serial.println(ip.toString());
      return;
    }
    delay(500);
    Serial.print(".");
    c++;
  }
}

void setup() {
  Serial.begin(115200);
  
  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.disconnect();

  //eraseSettings();
  //esp_restart();

  if(!initSettings()){
    Serial.println("There was an error initializing settings");
    esp_restart();
  }

  setVersion(version);
  String ssid = getSSID();

  macAddress = WiFi.macAddress();

  if(ssid.isEmpty()){
    setupAccessPoint();
  }else{
    connectToWifi(getSSID().c_str(), getNetworkKey().c_str());
    hasPreferences = true;

    if(WiFi.status() == WL_CONNECTED){
      Serial.println("Connected to WiFi");
      int cpId =  getControlPointId();
      Serial.println(cpId);

      if(cpId > 0){
        Serial.println("Initializing ESP Now");
        if(!InitEspNow()){
          return;
        }
        Serial.println("Launching Control Point Web");
        launchControlPointWeb();
      }else{
        launchRegisterWeb();
      }
    }else{
      Serial.println("Could not connect to WiFi. Starting over.");
      setupAccessPoint();
    }
  }
}

void loop() {
if(!hasPreferences){
    delay(1);
  }else{
    delay(100);

    int nodeIdToLog = GetNodeIdToLog();
    if(nodeIdToLog > 0){
      for(NodeReading r : GetNodeReadings()){
        if(r.nodeId == nodeIdToLog){
          delay(50);
          logNodeReading(getApiHost(), getApiPort(), r);
          delay(50);
        }
      }

      ReSetNodeIdToLog();
    } 
    
    // increment our time counter
    unsigned long currentMillis = millis();

    // restart every once in a while, currently 1 day
    if(currentMillis  >= restartInterval){
      ESP.restart();
    }

    // if WiFi is down, try reconnecting
    if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
      Serial.println(millis());
      Serial.println("Reconnecting to WiFi...");
      WiFi.disconnect();
      if(WiFi.reconnect()){
        int controlPointId = getControlPointId();
        if(controlPointId > 0){
          Serial.println("Updating API with new IP");
          updateAPIWithIpAddress(getApiHost(), getApiPort(), controlPointId, WiFi.localIP().toString());
        }
      }
      previousMillis = currentMillis;
    }
  }
}