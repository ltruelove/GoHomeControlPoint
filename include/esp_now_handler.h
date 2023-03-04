#ifndef ESP_NOW_HANDLER
#define ESP_NOW_HANDLER

#include <esp_now.h>
#include "node_reading.h"

bool InitEspNow();
void BroadcastData(bool triggerToggle, bool pressMomentary, int msMomentaryPress, bool triggerUpdate, bool eraseSettings, bool updateMode, String broadcastMac);
int GetNodeIdToLog();
void ReSetNodeIdToLog();

#endif