

#include "winsock_client.h"
#include "login.h"
#include "system.h"

int main() {
	int msg_int;
	InitSystem();

	SOCKET sock = StartWinsock();
	if (sock == -1) {
		puts("서버가 닫혀있거나 서버 주소 혹은 서버 포트가 서버와 일치하지 않습니다.");
		return 0;
	}

	msg_int = LoginMenu(sock);
	if (msg_int == 2) {
		goto ESC;
	}

	ESC: closesocket(sock);
	WSACleanup();
	return 0;
}