#ifndef NODE_READING
#define NODE_READING

#include <ArduinoJson.h>

struct NodeReading {
    int nodeId;
    float TemperatureF;
    float TemperatureC;
    float Humidity;
    int Moisture;
    int ResistorValue;
    int MagneticValue;
    bool IsClosed;
};

String SerializeNodeReading(NodeReading reading);

#endif