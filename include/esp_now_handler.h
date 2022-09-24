#ifndef ESP_NOW_HANDLER
#define ESP_NOW_HANDLER

#include <esp_now.h>
#include "node_reading.h"
#include "control_point_server.h"

bool InitEspNow();
void BroadcastData(bool triggerToggle, bool pressMomentary, int msMomentaryPress, String broadcastMac);

#endif