#ifndef NODE_READING
#define NODE_READING

#include <ArduinoJson.h>

class NodeReading{
public:
    String Serialize();
    int nodeId;
    float TemperatureF;
    float TemperatureC;
    float Humidity;
    int Moisture;
    int ResistorValue;
    bool IsClosed;
};

#endif