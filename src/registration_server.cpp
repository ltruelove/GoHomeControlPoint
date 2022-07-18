#include "registration_server.h"

AsyncWebServer registration_server(80);

void registerHome(AsyncWebServerRequest *request) {
    request->send(200, "text/html", register_index_html);
}

void registerControlPoint(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", register_control_point_html, processor);
}

void setRegisteredId(AsyncWebServerRequest *request){
    int controlPointId = 0;

    if(request->hasParam("controlPointId")){
        controlPointId = atoi(request->getParam("controlPointId")->value().c_str());
    }

    setControlPointId(controlPointId);
    request->send(200, "text/html", "Control point ID set");
}

void launchRegisterWeb(){
  registration_server.on("/", HTTP_GET, registerHome);
  registration_server.on("/register", HTTP_GET, registerControlPoint);
  registration_server.on("/clear", HTTP_GET, clearPreferences);
  registration_server.on("/setControlPointId", HTTP_POST, setRegisteredId);
  registration_server.onNotFound(handleNotFound);
  registration_server.begin();
}