#pragma once

#include <WinSock2.h>

#include "default_client.h"

#define PORT_NUM 12345
#define SERVER_IP "192.168.0.105"

SOCKET StartWinsock();
void CloseWinsock(SOCKET sock);