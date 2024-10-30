#ifndef API_WRAPPER
#define API_WRAPPER

void updateAPIWithIpAddress(String apiHost, String port, int controlPointId, String ipAddress);
void logNodeReading(String apiHost, String port, NodeReading reading);

#endif