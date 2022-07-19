#include "control_point_prefs.h"

Preferences prefs;

const char *prefsName = "cpPrefs";
String ssid = "";
String pass = "";
String apiHost = "";
uint16_t apiPort = 8080;
String name = "";
int controlPointId = 0;

void initPrefs(){
    prefs.begin(prefsName, true);
    ssid = prefs.getString("ssid", "");
    pass = prefs.getString("pass", "");
    apiHost = prefs.getString("apiHost", "");
    apiPort = prefs.getUInt("apiPort", 80);
    controlPointId = prefs.getUInt("controlPointId", 0);
    name = prefs.getString("name");
    prefs.end();

    Serial.println(ssid);
    Serial.println(pass);
    Serial.println(apiHost);
    Serial.println(apiPort);
    Serial.println(name);
    Serial.println(controlPointId);
}

bool isSSIDEmpty(){
    return ssid.isEmpty();
}

void setPrefs(String _ssid, String _pass, String _apiHost, int _apiPort, String _name, int _controlPointId){
    Serial.println(_ssid);
    Serial.println(_pass);
    Serial.println(_apiHost);
    Serial.println(_apiPort);
    Serial.println(_name);
    Serial.println(_controlPointId);

    prefs.begin(prefsName, false);
    prefs.putString("ssid", _ssid);
    prefs.putString("pass", _pass);
    prefs.putString("apiHost", _apiHost);
    prefs.putUInt("apiPort", _apiPort);
    prefs.putString("name", _name);
    prefs.putUInt("controlPointId", _controlPointId);
    prefs.end();
}

void clearPrefs(){
    prefs.begin(prefsName, false);
    prefs.clear();
    prefs.end();
}

void setControlPointId(int _controlPointId){
    prefs.begin(prefsName, false);
    prefs.putUInt("controlPointId", _controlPointId);
    prefs.end();
}

String getSSID(){
    return ssid;
}

String getNetworkKey(){
    return pass;
}

String getApiHost(){
    return apiHost;
}

int getApiPort(){
    return apiPort;
}

String getName(){
    return name;
}

int getControlPointId(){
    return controlPointId;
}