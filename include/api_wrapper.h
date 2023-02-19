#ifndef API_WRAPPER
#define API_WRAPPER

void updateAPIWithIpAddress(String apiHost, int port, int controlPointId, String ipAddress);
void logNodeReading(String apiHost, int port, NodeReading reading);

#endif