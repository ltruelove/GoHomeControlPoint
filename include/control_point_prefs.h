#ifndef CONTROL_POINT_PREFS
#define CONTROL_POINT_PREFS

#include <Preferences.h>

void initPrefs();
bool isSSIDEmpty();
void setPrefs(String _ssid, String _pass, String _apiHost, int _apiPort, String _name, int _controlPointId);
void savePrefs();
void clearPrefs();
void setControlPointId(int _controlPointId);
String getSSID();
String getNetworkKey();
String getApiHost();
void setApiHost(String ipAddress);
int getApiPort();
String getName();
int getControlPointId();

#endif