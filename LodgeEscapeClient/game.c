#include <WinSock2.h>
#include <stdbool.h>

#include "system.h"
#include "game.h"

void LoadGame(SOCKET);
int Option(SOCKET);
void Ending(SOCKET);

int StartGame(SOCKET sock, int num_player)
{

	while (true) {

		system("cls");

		int x, y;
		int msg_int;
		int key = 0;

		x = 2;
		y = 0;

		MoveCursor(x - 2, y);
		printf("> start game");

		MoveCursor(x, y + 2);
		printf("load game");

		MoveCursor(x, y + 4);
		printf("option");

		MoveCursor(x, y + 6);
		printf("ending");

		MoveCursor(x, y + 8);
		printf("exit");

		while (key != 4) {
			key = ControlKey();

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
				if (y < 8) {
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
					printf("start game is developing \n");
					system("pause");
					break;
				}

				case LOAD_GAME: {
					LoadGame(sock);
					break;
				}

				case OPTION: {
					y = Option(sock);

					if (y == 1) {
						return 0;
					}
					break;
				}

				case ENDING: {
					Ending(sock);
					break;
				}

				case EXIT: {
					return y;
					break;
				}

				}

				break;
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
		printf("불러올 수 있는 게임 정보가 없습니다. \n");
	}

	else {
		for (msg_int; msg_int > 0; --msg_int) {
			recv(sock, &msg_int, sizeof(msg_int), 0);
			printf("챕터 : %d \n", msg_int);

			recv(sock, &msg_int, sizeof(msg_int), 0);
			printf("스테이지 : %d \n \n", msg_int);
		}
	}

	system("pause");
}

int Option(SOCKET sock)
{
	char msg_char[MAX_MSG_LEN] = "";
	int msg_int;
	int x, y;

	x = 2;
	y = 0;

	MoveCursor(x - 2, y);
	printf("> 로그인 정보");
	
	MoveCursor(x, y + 2);
	printf("로그아웃");

	MoveCursor(x, y + 4);
	printf("되돌아가기");

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
			if (y < 4) {
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

			case LOGIN_DATA: {
				recv(sock, msg_char, MAX_MSG_LEN, 0);
				printf("ID : %s \n", msg_char);

				recv(sock, msg_char, MAX_MSG_LEN, 0);
				printf("비밀번호 : %s \n", msg_char);

				recv(sock, &msg_int, sizeof(msg_int), 0);
				printf("플레이어 번호 : %d \n", msg_int);

				recv(sock, &msg_int, sizeof(msg_int), 0);
				printf("발견한 엔딩 : %d개 \n", msg_int);

				system("pause");

				return y;
			}

			default: {
				return y;
			}

			}
		}

		}
	}
}

void Ending(SOCKET sock)
{
	char msg_char[MAX_MSG_LEN] = "";
	int msg_int;

	for (int i = 0; i < NUM_MAX_ENDING; ++i) {

		printf("엔딩 번호 : %d \n", i + 1);

		recv(sock, &msg_int, sizeof(msg_int), 0);

		if (msg_int == 1) {
			recv(sock, msg_char, MAX_MSG_LEN, 0);

			printf("엔딩 : %s \n", msg_char);
		}

		else {
			printf("엔딩 : 아직 발견하지 못함 \n \n");
		}
		
	}

	system("pause");
}