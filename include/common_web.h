#ifndef COMMON_WEB
#define COMMON_WEB

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "control_point_prefs.h"

String processor(const String& var);
String scanNetworks();
void clearPreferences(AsyncWebServerRequest *request);
void handleNotFound(AsyncWebServerRequest *request);
void setOTA(AsyncWebServer *server);

#endif