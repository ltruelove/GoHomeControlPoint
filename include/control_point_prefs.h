#ifndef CONTROL_POINT_PREFS
#define CONTROL_POINT_PREFS

#include <Arduino.h>
#include "settings.h"

void clearPrefs();

String getSSID();
String getNetworkKey();
String getApiHost();
int getControlPointId();
String getApiPort();
String getName();
String getVersion();

void setApiHost(String ipAddress);
void setApiPort(String _port);
void setSSID(String _ssid);
void setPass(String _pass);
void setApiHost(String _apiHost);
void setName(String _name);
void setControlPointId(int _controlPointId);
void setVersion(String _version);

#endif