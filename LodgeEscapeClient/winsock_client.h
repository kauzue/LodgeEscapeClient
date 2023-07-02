#pragma once
#pragma comment(lib,"ws2_32")
#pragma warning(disable:4996)

#include <WinSock2.h>

#define PORT_NUM 12345
#define SERVER_IP "192.168.0.105"

SOCKET StartWinsock();
void CloseWinsock(SOCKET sock);