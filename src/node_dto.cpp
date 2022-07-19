#include "node_dto.h"

Node::Node(){
    Name = "";
    Mac = "";
}

NodeSensor::NodeSensor(){
    Name = "";
    SensorTypeId = 0;
    Pin = 0;
    DHTType = 0;
}

NodeSwitch::NodeSwitch(){
    Name = "";
    SwitchTypeId = 0;
    Pin = 0;
    MomentaryPressDuration = 0;
    IsClosedOn = 0;
}

NodeDTO::NodeDTO(){
    Node node();
    std::vector<NodeSensor> sensors;
    std::vector<NodeSwitch> switches;
}

void NodeDTO::PopulateFromJson(String nodeDtoJsonString){
    DynamicJsonDocument doc(1024);
    DynamicJsonDocument sensorsDoc(1024);
    DynamicJsonDocument switchesDoc(1024);
    deserializeJson(doc, nodeDtoJsonString);
    deserializeJson(sensorsDoc, doc["Sensors"]);
    deserializeJson(switchesDoc, doc["Switches"]);

    JsonArray sensorArray = sensorsDoc.to<JsonArray>();
    JsonArray switchArray = switchesDoc.to<JsonArray>();

    node.Name = doc["Node"]["Name"].as<String>();
    node.Mac = doc["Node"]["Mac"].as<String>();

    for(JsonVariant v : sensorArray){
        NodeSensor sensor;
        sensor.Name = v["Name"].as<String>();
        sensor.SensorTypeId = v["SensorTypeId"];
        sensor.Pin = v["Pin"];
        sensor.DHTType = v["DHTType"];

        sensors.push_back(sensor);
    }

    for(JsonVariant v : switchArray){
        NodeSwitch nodeSwitch;
        nodeSwitch.Name = v["Name"].as<String>();
        nodeSwitch.SwitchTypeId = v["SwitchTypeId"];
        nodeSwitch.Pin = v["Pin"];

        switches.push_back(nodeSwitch);
    }

}

String NodeDTO::Serialize(){
    DynamicJsonDocument doc(1024);

    String output;
    doc["Node"]["Name"] = node.Name;
    doc["Node"]["Mac"] = node.Mac;

    int i = 0;
    for(NodeSensor s : sensors){
        doc["Sensors"][i]["Name"] = s.Name;
        doc["Sensors"][i]["SensorTypeId"] = s.SensorTypeId;
        doc["Sensors"][i]["Pin"] = s.Pin;
        doc["Sensors"][i]["DHTType"] = s.DHTType;
        i++;
    }

    i = 0;
    for(NodeSwitch s : switches){
        doc["Sensors"][i]["Name"] = s.Name;
        doc["Sensors"][i]["SwitchTypeId"] = s.SwitchTypeId;
        doc["Sensors"][i]["Pin"] = s.Pin;
        doc["Sensors"][i]["MomentaryPressDuration"] = s.MomentaryPressDuration;
        doc["Sensors"][i]["IsClosedOn"] = s.IsClosedOn;
        i++;
    }

    serializeJson(doc, output);

    return output;
}