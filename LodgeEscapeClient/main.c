
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
		puts("������ �����ְų� ���� �ּ� Ȥ�� ���� ��Ʈ�� ������ ��ġ���� �ʽ��ϴ�.");
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