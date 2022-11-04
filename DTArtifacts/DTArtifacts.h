#pragma once

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

const char* DREAMTEA_IP = "dreamtea.io";
const char* DTA_PORT = "7676";

void connect(const char* ip, const char* port);
