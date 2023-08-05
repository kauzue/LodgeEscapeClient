#include <WinSock2.h>
#include <stdbool.h>

#include "system.h"
#include "game.h"

void LoadGame(SOCKET);

void StartGame(SOCKET sock, int num_player)
{

	while (true) {

		int x, y;
		int msg_int;

		x = 2;
		y = 0;

		MoveCursor(x - 2, y);
		printf("> start game");

		MoveCursor(x, y + 2);
		printf("load game");

		MoveCursor(x, y + 4);
		printf("option");

		MoveCursor(x, y + 6);
		printf("exit");

		while (true) {
			int key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 0) {
					MoveCursor(x - 2, y);
					printf(" ");
					MoveCursor(x - 2, y -= 2);
					printf(">");
				}
				break;
			}

			case DOWN: {
				if (y < 6) {
					MoveCursor(x - 2, y);
					printf(" ");

					MoveCursor(x - 2, y += 2);
					printf(">");
				}
				break;
			}

			case ENTER: {

				y = y / 2;

				system("cls");

				send(sock, &y, sizeof(y), 0);

				switch (y) {

				case START_GAME: {
					printf("start game");
					break;
				}

				case LOAD_GAME: {
					LoadGame(sock);
					break;
				}

				case OPTION: {
					printf("option");
					break;
				}

				case EXIT: {
					printf("exit");
					return;
					break;
				}

				}
			}

			}
		}
	}
}

void FirstPlayer()
{

}

void SecondPlayer()
{

}

void LoadGame(SOCKET sock)
{
	int msg_int;

	recv(sock, &msg_int, sizeof(msg_int), 0);

	if (msg_int == 0) {
		printf("불러올 수 있는 게임 정보가 없습니다.");
	}

	else {
		for (msg_int; msg_int > 0; --msg_int) {
			recv(sock, &msg_int, sizeof(msg_int), 0);
			printf("챕터 : %d \n", msg_int);

			recv(sock, &msg_int, sizeof(msg_int), 0);
			printf("스테이지 : %d \n \n", msg_int);
		}
	}
}