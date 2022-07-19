#include "control_point_server.h"

AsyncWebServer control_point_server(80);
//AsyncEventSource events("/events");

std::vector<NodeReading> readings;

void controlPointHome(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", controlPoint_index_html, processor);
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

    request->send(200, "application/json", output);
}

void launchControlPointWeb(){
  Serial.println("control point web");
  control_point_server.on("/", HTTP_GET, controlPointHome);
  control_point_server.on("/nodeData", HTTP_POST, getNodeData);
  control_point_server.on("/clear", HTTP_GET, clearPreferences);
  control_point_server.onNotFound(handleNotFound);
  
  control_point_server.begin();
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