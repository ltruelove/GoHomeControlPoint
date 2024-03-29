#include "initial_server.h"
#include "SPIFFS.h"

AsyncWebServer initial_server(80);

void wifiHome(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/wifi_index.html");
}

void wifiSetupPage(AsyncWebServerRequest *request){
  request->send(SPIFFS, "/wifi_select_form.html", String(), false, processor);
}

void setParameters(AsyncWebServerRequest *request){
    String ssid, pass, apiHost, name;
    uint16_t apiPort = 80;

    if(request->hasParam("ssid")){
        ssid = request->getParam("ssid")->value();
    }

    if(request->hasParam("pass")){
        pass = request->getParam("pass")->value();
    }

    if(request->hasParam("apiHost")){
        apiHost = request->getParam("apiHost")->value();
    }

    if(request->hasParam("apiPort")){
        apiPort = (uint16_t)atoi(request->getParam("apiPort")->value().c_str());
    }

    if(request->hasParam("name")){
        name = request->getParam("name")->value();
    }

    if (ssid.length() > 0 && pass.length() > 0) {
        setSSID(ssid);
        setPass(pass);
        setApiHost(apiHost);
        setName(name);
        setApiPort(apiPort);

        String message = "{\"Success\":\"saved to flash... resetting to boot into new wifi\"}";
        request->send(200, "application/json", message);
        
        delay(100);
        ESP.restart();
        return;
    }

  String message = "{\"Error\":\"404 not found\"}";
  request->send(404, "application/json", message);
}

void launchWeb(){
  Serial.println("");

  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());

  initial_server.on("/", HTTP_GET, wifiHome);
  initial_server.on("/wifi-setup", HTTP_GET, wifiSetupPage);
  initial_server.on("/setting", HTTP_GET, setParameters);
  initial_server.on("/clear", HTTP_GET, clearPreferences);
  initial_server.on("/version", HTTP_GET, controlPointVersion);
  initial_server.onNotFound(handleNotFound);

  setOTA(&initial_server);

  Serial.println("begin initial server");
  initial_server.begin();
  Serial.println("Web Server started");
}

void setupAccessPoint(void)
{
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  delay(100);

  WiFi.softAP("GoHome Control Point Setup", "");
  launchWeb();
}