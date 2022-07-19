#include "node_reading.h"

String NodeReading::Serialize(){

    DynamicJsonDocument doc(1024);

    doc["nodeId"] = nodeId;
    doc["TemperatureF"] = TemperatureF;
    doc["TemperatureC"] = TemperatureC;
    doc["Humidity"] = Humidity;
    doc["Moisture"] = Moisture;
    doc["ResistorValue"] = ResistorValue;
    doc["IsClosed"] = IsClosed;

    String output;
    serializeJson(doc, output);

    return output;
}