#include <Arduino.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>

#include "node_reading.h"
#include "api_wrapper.h"
#include "settings.h"

void updateAPIWithIpAddress(String apiHost, int port, int controlPointId, String ipAddress){
    WiFiClient client;
    HTTPClient http;

    String updateEndpoint = "http://" + apiHost;
    if(port != 80){
        updateEndpoint += ":" + (String)port;
    }
    updateEndpoint += "/controlPoint/ipUpdate";

    http.begin(client, updateEndpoint);

    DynamicJsonDocument doc(1024);

    doc["Id"] = controlPointId;
    doc["IpAddress"] = ipAddress;

    String serializedString;
    serializeJson(doc, serializedString);

    int httpResponseCode = http.POST(serializedString);

    if(httpResponseCode != 200){
        Serial.print("Register request failed with response code: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}

void logNodeReading(String apiHost, int port, NodeReading reading){
    WiFiClient client;
    HTTPClient http;

    String updateEndpoint = "http://" + apiHost;
    if(port != 80){
        updateEndpoint += ":" + (String)port;
    }
    updateEndpoint += "/node/reading";

    http.begin(client, updateEndpoint);

    DynamicJsonDocument doc(1024);

    doc["nodeId"] = reading.nodeId;
    doc["TemperatureF"] = reading.TemperatureF;
    doc["TemperatureC"] = reading.TemperatureC;
    doc["Humidity"] = reading.Humidity;
    doc["Moisture"] = reading.Moisture;
    doc["ResistorValue"] = reading.ResistorValue;
    doc["IsClosed"] = reading.IsClosed;

    String serializedString;
    serializeJson(doc, serializedString);

    int httpResponseCode = http.POST(serializedString);

    if(httpResponseCode != 200){
        http.end();
        Serial.println("error");
        Serial.print("Log reading request failed with response code: ");
        Serial.println(httpResponseCode);
    }
}