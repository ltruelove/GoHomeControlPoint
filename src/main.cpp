#include <Arduino.h>
#include <WiFi.h>

#include "control_point_prefs.h"
#include "registration_server.h"
#include "initial_server.h"
#include "control_point_server.h"
#include "esp_now_handler.h"

AsyncWebServer server(80);

unsigned long previousMillis = 0;
unsigned long interval = 30000;
bool isConnected = false;
bool hasPreferences = false;
String macAddress;

void connectToWifi(const char *ssid, const char *key){
  WiFi.mode(WIFI_AP_STA);
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
  
  WiFi.disconnect();

  Serial.println("getting preferences");
  initPrefs();

  macAddress = WiFi.macAddress();

  Serial.println("Check for empty SSID");
  if(isSSIDEmpty()){
    Serial.println("empty ssid");
    setupAccessPoint();
  }else{
    connectToWifi(getSSID().c_str(), getNetworkKey().c_str());

    if(WiFi.status() == WL_CONNECTED){
      Serial.println("Connected to WiFi");
      int cpId =  getControlPointId();
      Serial.println(cpId);

      if(cpId > 0){
        //TODO handle ESP Now requests as well.
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
  // put your main code here, to run repeatedly:
}