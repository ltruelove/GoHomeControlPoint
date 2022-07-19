#include "esp_now_handler.h"

NodeReading nowReading;

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
}

bool InitEspNow(){
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return false;
    }

    esp_now_register_recv_cb(OnDataRecv);
    return true;
}