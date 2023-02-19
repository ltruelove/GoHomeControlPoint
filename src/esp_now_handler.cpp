#include "esp_now_handler.h"
#include "api_wrapper.h"

NodeReading nowReading;
esp_now_peer_info_t peerInfo;

int nodeIdToLog = 0;

struct SwitchCommand {
    bool triggerToggle;
    bool pressMomentary;
    int msMomentaryPress;
    bool triggerUpdate;
    bool eraseSettings;
};

SwitchCommand command;

void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) { 
    // Copies the sender mac address to a string
    char macStr[18];
    Serial.print("Packet received from: ");
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.println(macStr);
    memcpy(&nowReading, incomingData, sizeof(nowReading));
    
    // store the reading for fetching later
    addReading(nowReading);
    
    // Can't call the logging endpoint in the middle of an ESP Now operation for some reason.
    // So I moved it to the main loop and check this nodeIdToLog value to see if I need to log it.
    nodeIdToLog = nowReading.nodeId;
}

void ReSetNodeIdToLog(){
    nodeIdToLog = 0;
}

int GetNodeIdToLog(){
    return nodeIdToLog;
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

bool InitEspNow(){
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return false;
    }

    esp_now_register_recv_cb(OnDataRecv);
    esp_now_register_send_cb(OnDataSent);
    return true;
}

void addPeer(uint8_t* mac){
    memcpy(peerInfo.peer_addr, mac, 6);
    peerInfo.encrypt = false;
    
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }
}

uint8_t * stringToMac(String macString){
    static uint8_t macArray[6];
    char delim[] = ":";
    char *strings[30];
    int i = 0;

    char *mac_arr = new char[macString.length() + 1];
    strcpy(mac_arr, macString.c_str());
    Serial.println(mac_arr);

    strings[i] = strtok(mac_arr, delim);
    while(strings[i] != NULL){
        strings[++i] = strtok(NULL, delim);
    }

    delete [] mac_arr;

    for(int j = 0; j < i; j++){
        macArray[j] = (int)strtol(strings[j], NULL, 16);
    }

    return macArray;
}

void BroadcastData(bool triggerToggle, bool pressMomentary, int msMomentaryPress, bool triggerUpdate, bool eraseSettings, String broadcastMac){
    command.triggerToggle = triggerToggle;
    command.pressMomentary = pressMomentary;
    command.msMomentaryPress = msMomentaryPress;
    command.triggerUpdate = triggerUpdate;
    command.eraseSettings = eraseSettings;
    uint8_t* mac = stringToMac(broadcastMac);

    if(!esp_now_is_peer_exist(mac)){
        addPeer(mac);
    }

    Serial.println(command.triggerUpdate);
    esp_err_t result = esp_now_send(mac, (uint8_t *) &command, sizeof(command));

    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }
}