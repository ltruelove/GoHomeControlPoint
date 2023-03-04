#include "control_point_server.h"
#include "esp_now_handler.h"
#include "api_wrapper.h"
#include "SPIFFS.h"

AsyncWebServer control_point_server(80);
//AsyncEventSource events("/events");

std::vector<NodeReading> readings;

void controlPointHome(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/controlPoint_index.html", String(), false, processor);
}

void controlPointUpdateIp(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/api_ip_change_form.html");
}

std::vector<NodeReading> GetNodeReadings(){
  return readings;
}

void getNodeData(AsyncWebServerRequest *request) {
    int nodeId = 0;

    if(!request->hasParam("nodeId")){
      request->send(400, "text/html", "nodeId is required");
      return;
    }

    nodeId = atoi(request->getParam("nodeId")->value().c_str());

    String output;
    for(NodeReading reading : readings){
      if(reading.nodeId == nodeId){
        output = SerializeNodeReading(reading);
      }
    }

    if(output.isEmpty()){
      request->send(404, "text/html", "Could not find requested node data");
    }

    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", output);
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
}

void apiIpUpdate(AsyncWebServerRequest *request) {
  if(!request->hasParam("IpAddress", true)){
    request->send(400, "text/html", "IP address is required");
    return;
  }

  String ipAddress = request->getParam("IpAddress", true)->value();
  int port;

  if(!request->hasParam("Port", true)){
    port = atoi(request->getParam("Port", true)->value().c_str());
  }

  Serial.println(ipAddress);

  setApiHost(ipAddress);
  setApiPort(port);
  
  AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "IP address saved");
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);

  delay(100);
  ESP.restart();
}

void toggleNodeSwitch(AsyncWebServerRequest *request) {
  String mac = "";

  if(!request->hasParam("mac")){
    request->send(400, "text/html", "node MAC address is required");
    return;
  }

  mac = request->getParam("mac")->value().c_str();
  BroadcastData(true, false, 0, false, false, false, mac);

  AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "");
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

void pressMomentary(AsyncWebServerRequest *request) {
  String mac = "";
  int duration = 0;

  if(!request->hasParam("mac")){
    request->send(400, "text/html", "node MAC address is required");
    return;
  }

  if(!request->hasParam("MomentaryPressDuration")){
    request->send(400, "text/html", "MomentaryPressDuration is required");
    return;
  }

  mac = request->getParam("mac")->value().c_str();
  duration = atoi(request->getParam("MomentaryPressDuration")->value().c_str());

  BroadcastData(false, true, duration, false, false, false, mac);

  AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "");
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

void triggerUpdate(AsyncWebServerRequest *request) {
  String mac = "";

  if(!request->hasParam("mac")){
    request->send(400, "text/html", "node MAC address is required");
    return;
  }

  mac = request->getParam("mac")->value().c_str();

  BroadcastData(false, false, 0, true, false, false, mac);

  AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "");
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

void eraseNodeSettings(AsyncWebServerRequest *request) {
  String mac = "";

  if(!request->hasParam("mac")){
    request->send(400, "text/html", "node MAC address is required");
    return;
  }

  mac = request->getParam("mac")->value().c_str();
  BroadcastData(false, false, 0, false, true, false, mac);

  AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "");
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

void putInUpdateMode(AsyncWebServerRequest *request) {
  String mac = "";

  if(!request->hasParam("mac")){
    request->send(400, "text/html", "node MAC address is required");
    return;
  }

  mac = request->getParam("mac")->value().c_str();
  BroadcastData(false, false, 0, false, false, true, mac);

  AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "");
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

void launchControlPointWeb(){
  Serial.println("control point web");
  control_point_server.on("/", HTTP_GET, controlPointHome);
  control_point_server.on("/updateIp", HTTP_GET, controlPointUpdateIp);
  control_point_server.on("/nodeData", HTTP_GET, getNodeData);
  control_point_server.on("/apiIpUpdate", HTTP_POST, apiIpUpdate);
  control_point_server.on("/clear", HTTP_GET, clearPreferences);
  control_point_server.on("/toggleNodeSwitch", HTTP_GET, toggleNodeSwitch);
  control_point_server.on("/pressMomentary", HTTP_GET, pressMomentary);
  control_point_server.on("/triggerUpdate", HTTP_GET, triggerUpdate);
  control_point_server.on("/eraseNodeSettings", HTTP_GET, eraseNodeSettings);
  control_point_server.on("/nodeUpdateMode", HTTP_GET, putInUpdateMode);
  control_point_server.onNotFound(handleNotFound);
 
  setOTA(&control_point_server);
 
  Serial.println("begin control point server");
  control_point_server.begin();

  updateAPIWithIpAddress(getApiHost(), getApiPort(), getControlPointId(), WiFi.localIP().toString());
}

void addReading(NodeReading reading){
    int i = 0;
    int existingIndex = -1;

    for(NodeReading r : readings){
      if(r.nodeId == reading.nodeId){
        existingIndex = i;
      }

      i++;
    }

  if(existingIndex > -1){
    readings[existingIndex] = reading;
  }else{
    readings.push_back(reading);
  }

}