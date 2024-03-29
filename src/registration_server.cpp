#include "registration_server.h"
#include "SPIFFS.h"

AsyncWebServer registration_server(80);

void registerHome(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/register_index.html");
}

void registerControlPoint(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/register_controlPoint.html", String(), false, processor);
}

void setRegisteredId(AsyncWebServerRequest *request){
    int controlPointId = 0;

    if(!request->hasParam("controlPointId", true)){
        request->send(400, "text/html", "controlPointId is required");
        return;
    }

    controlPointId = atoi(request->getParam("controlPointId", true)->value().c_str());

    setControlPointId(controlPointId);
    request->send(200, "text/html", "Control point ID set");
}

void restart(AsyncWebServerRequest *request){
  request->send(200, "application/json", "restarting");

  delay(100);
  ESP.restart();
}

void launchRegisterWeb(){
  registration_server.on("/", HTTP_GET, registerHome);
  registration_server.on("/register", HTTP_GET, registerControlPoint);
  registration_server.on("/clear", HTTP_GET, clearPreferences);
  registration_server.on("/setControlPointId", HTTP_POST, setRegisteredId);
  registration_server.on("/restart", HTTP_GET, restart);
  registration_server.on("/version", HTTP_GET, controlPointVersion);
  registration_server.onNotFound(handleNotFound);

  setOTA(&registration_server);

  Serial.println("begin registration server");
  registration_server.begin();
}