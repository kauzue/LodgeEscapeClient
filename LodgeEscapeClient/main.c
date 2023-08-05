
#include "winsock_client.h"
#include "login.h"
#include "system.h"
#include "game.h"

int main() {
	int num_player;
	InitSystem();

	SOCKET sock = StartWinsock();
	if (sock == -1) {
		puts("������ �����ְų� ���� �ּ� Ȥ�� ���� ��Ʈ�� ������ ��ġ���� �ʽ��ϴ�.");
		return 0;
	}

	num_player = LoginMenu(sock);
	if (num_player == 0) {
		goto ESC;
	}

	StartGame(sock, num_player);

	ESC: closesocket(sock);
	WSACleanup();
	return 0;
}