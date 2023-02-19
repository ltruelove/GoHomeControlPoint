#include "control_point_prefs.h"

const char *SSID = "ssid", *PASS = "pass", *API_HOST = "apiHost", *NODE_NAME = "name", *CTRL_PT_ID = "controlPointId", *API_PORT = "apiPort";

void clearPrefs(){
    eraseSettings();
}

String getSSID(){
    return getStringValue(SSID);
}

String getNetworkKey(){
    return getStringValue(PASS);
}

String getApiHost(){
    return getStringValue(API_HOST);
}

String getName(){
    return getStringValue(NODE_NAME);
}

int getControlPointId(){
    return getIntValue(CTRL_PT_ID);
}

int getApiPort(){
    return getIntValue(API_PORT);
}

void setApiPort(int port){
    setIntValue(port, API_PORT);
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