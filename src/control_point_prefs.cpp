#include "control_point_prefs.h"

const char *SSID = "ssid", *PASS = "pass", *API_HOST = "apiHost", *NODE_NAME = "name", *CTRL_PT_ID = "controlPointId", *API_PORT = "apiPort", *VERSION = "version";

String ssid;
String networkKey;
String apiHost;
String name;
int controlPointId;
String apiPort;
String version;

void initControlPointPrefs(){
    ssid = getStringValue(SSID);
    networkKey = getStringValue(PASS);
    apiHost = getStringValue(API_HOST);
    name = getStringValue(NODE_NAME);
    controlPointId = getIntValue(CTRL_PT_ID);
    apiPort = getStringValue(API_PORT);
    version = getStringValue(VERSION);
}

void clearPrefs(){
    eraseSettings();
}

String getSSID(){
    return ssid;
}

String getNetworkKey(){
    return networkKey;
}

String getApiHost(){
    return apiHost;
}

String getName(){
    return name;
}

int getControlPointId(){
    return controlPointId;
}

String getApiPort(){
    return apiPort;
}

String getVersion(){
    return version;
}

void setApiPort(String _port){
    setStringValue(_port.c_str(), API_PORT);
}

void setSSID(String _ssid){
    setStringValue(_ssid.c_str(), SSID);
}

void setPass(String _pass){
    setStringValue(_pass.c_str(), PASS);
}

void setApiHost(String _apiHost){
    setStringValue(_apiHost.c_str(), API_HOST);
}

void setName(String _name){
    setStringValue(_name.c_str(), NODE_NAME);
}

void setControlPointId(int _controlPointId){
    setIntValue(_controlPointId, CTRL_PT_ID);
}

void setVersion(String _version){
    setStringValue(_version.c_str(), VERSION);
}