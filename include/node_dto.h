#ifndef NODE_DTO
#define NODE_DTO

#include <ArduinoJson.h>
#include <vector>

class Node {
public:
    Node();
    String Name;
    String Mac;
};

class NodeSensor {
public:
    NodeSensor();
    String Name;
    int SensorTypeId;
    int Pin;
    int DHTType;
};

class NodeSwitch {
public:
    NodeSwitch();
    String Name;
    int SwitchTypeId;
    int Pin;
    int MomentaryPressDuration;
    bool IsClosedOn;
};

class NodeDTO {
public:
    NodeDTO();
    void PopulateFromJson(String nodeDtoJsonString);
    String Serialize();
    Node node;
    std::vector<NodeSensor> sensors;
    std::vector<NodeSwitch> switches;
};

#endif