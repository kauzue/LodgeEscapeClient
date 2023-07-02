

#include "winsock_client.h"
#include "game.h"


int main() {
	SOCKET sock = StartWinsock();
	if (sock == -1)
	{
		return 0;
	}

	LoginMenu();

	CloseWinsock(sock);
	return 0;
}