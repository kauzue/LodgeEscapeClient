#include "winsock_client.h"

SOCKET StartWinsock()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int e = WSAGetLastError();
	if (sock == -1) {
		return -1;
	}

	SOCKADDR_IN servaddr = { 0 };
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	servaddr.sin_port = htons(PORT_NUM);

	int re = 0;
	re = connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if (re == 1) {
		return -1;
	}

	return sock;
}

void CloseWinsock(SOCKET sock)
{
	closesocket(sock);
	WSACleanup();
}