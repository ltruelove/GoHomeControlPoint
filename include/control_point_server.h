#ifndef CONTROL_POINT_SERVER
#define CONTROL_POINT_SERVER

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include <Update.h>

#include "control_point_prefs.h"
#include "common_web.h"
#include "node_reading.h"

void launchControlPointWeb();
void addReading(NodeReading reading);
std::vector<NodeReading> GetNodeReadings();

#endif