

#include "winsock_client.h"
#include "login.h"
#include "system.h"

int main() {
	int msg_int;
	InitSystem();

	SOCKET sock = StartWinsock();
	if (sock == -1) {
		puts("������ �����ְų� ���� �ּ� Ȥ�� ���� ��Ʈ�� ������ ��ġ���� �ʽ��ϴ�.");
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