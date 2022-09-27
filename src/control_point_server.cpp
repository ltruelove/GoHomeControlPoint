#include "control_point_server.h"
#include "esp_now_handler.h"

AsyncWebServer control_point_server(80);
//AsyncEventSource events("/events");

std::vector<NodeReading> readings;

void controlPointHome(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", controlPoint_index_html, processor);
}

void controlPointUpdateIp(AsyncWebServerRequest *request) {
    request->send(200, "text/html", api_ip_change_form);
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

void updateAPIWithIpAddress(){
  WiFiClient client;
  HTTPClient http;

  String updateEndpoint = "http://" + getApiHost();
  int port = getApiPort();
  if(port != 80){
    updateEndpoint += ":" + (String)port;
  }
  updateEndpoint += "/controlPoint/ipUpdate";

  Serial.println(updateEndpoint);
  Serial.println(WiFi.localIP());
  http.begin(client, updateEndpoint);

  DynamicJsonDocument doc(1024);

  doc["Id"] = getControlPointId();
  doc["IpAddress"] = WiFi.localIP().toString();

  String serializedString;
  serializeJson(doc, serializedString);

  Serial.println("Payload:");
  Serial.println(serializedString);
  int httpResponseCode = http.POST(serializedString);

  if(httpResponseCode != 200){
    http.end();
    Serial.print("Register request failed with response code: ");
    Serial.println(httpResponseCode);
  }
}

void apiIpUpdate(AsyncWebServerRequest *request) {
  if(!request->hasParam("IpAddress", true)){
    request->send(400, "text/html", "nodeId is required");
    return;
  }

  String ipAddress = request->getParam("IpAddress", true)->value();

  Serial.println(ipAddress);

  setApiHost(ipAddress);
  request->send(200, "text/html", "IP Address saved");

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
    BroadcastData(true, false, 0, false, mac);

    request->send(200, "application/json", "");
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
    duration = atoi(request->getParam("mac")->value().c_str());

    BroadcastData(false, true, duration, false, mac);

    request->send(200, "application/json", "");
}

void triggerUpdate(AsyncWebServerRequest *request) {
    String mac = "";

    if(!request->hasParam("mac")){
      request->send(400, "text/html", "node MAC address is required");
      return;
    }

    mac = request->getParam("mac")->value().c_str();
    BroadcastData(false, false, 0, true, mac);

    request->send(200, "application/json", "");
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
  control_point_server.onNotFound(handleNotFound);
  
  control_point_server.begin();
  updateAPIWithIpAddress();
  /*
  control_point_server.on("/restart", HTTP_GET, restart);
  control_point_server.on("/register", HTTP_GET, registerControlPoint);
  */
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