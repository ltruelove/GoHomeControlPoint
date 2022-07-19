#ifndef INITIAL_SERVER
#define INITIAL_SERVER

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "control_point_prefs.h"
#include "common_web.h"
#include "pages.h"

void launchWeb();

void setupAccessPoint(void);

#endif