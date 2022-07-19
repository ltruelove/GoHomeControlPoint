#include "node_reading.h"

String SerializeNodeReading(NodeReading reading){

    DynamicJsonDocument doc(1024);

    doc["nodeId"] = reading.nodeId;
    doc["TemperatureF"] = reading.TemperatureF;
    doc["TemperatureC"] = reading.TemperatureC;
    doc["Humidity"] = reading.Humidity;
    doc["Moisture"] = reading.Moisture;
    doc["ResistorValue"] = reading.ResistorValue;
    doc["IsClosed"] = reading.IsClosed;

    String output;
    serializeJson(doc, output);

    return output;
}