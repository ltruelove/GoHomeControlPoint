#ifndef NODE_READING
#define NODE_READING

#include <ArduinoJson.h>

typedef struct NodeReading {
    int nodeId;
    float TemperatureF;
    float TemperatureC;
    float Humidity;
    int Moisture;
    int ResistorValue;
    bool IsClosed;
};

String SerializeNodeReading(NodeReading reading);

#endif