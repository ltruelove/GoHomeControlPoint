#ifndef REGISTRATION_SERVER
#define REGISTRATION_SERVER

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "control_point_prefs.h"
#include "common_web.h"
#include "pages.h"

void launchRegisterWeb();

#endif