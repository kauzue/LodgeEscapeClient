

#include "winsock_client.h"
#include "game.h"


int main() {
	SOCKET sock = StartWinsock();
	if (sock == -1)
	{
		return 0;
	}

	sned(sock, LoginMenu(), sizeof(int), 0);

	CloseWinsock(sock);
	return 0;
}
