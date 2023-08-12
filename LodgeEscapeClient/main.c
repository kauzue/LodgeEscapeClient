
#include "winsock_client.h"
#include "login.h"
#include "system.h"
#include "game.h"

int main() {
	int err_player;
	int login = 0;

	InitSystem();

	SOCKET sock = StartWinsock();
	if (sock == -1) {
		puts("서버가 닫혀있거나 서버 주소 혹은 서버 포트가 서버와 일치하지 않습니다.");
		return 0;
	}
	
	while(!login) {

		err_player = LoginMenu(sock);
		if (err_player == 0) {
			break;
		}

		login = StartGame(sock);
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}