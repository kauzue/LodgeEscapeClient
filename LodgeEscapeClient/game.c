#pragma warning(disable:4996)

#include <WinSock2.h>
#include <stdbool.h>
#include <stdio.h>

#include "system.h"
#include "game.h"

void DefaultPlayer(SOCKET);
int CreateRoom(SOCKET);
int FindRoom(SOCKET);
void LoadGame(SOCKET);
int Option(SOCKET);
void Ending(SOCKET);

int StartGame(SOCKET sock)
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
					DefaultPlayer(sock);
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

void DefaultPlayer(SOCKET sock)
{
	int x, y;
	int msg_int;

	x = 2;
	y = 0;

	MoveCursor(x - 2, y);
	printf("> create room");

	MoveCursor(x, y + 2);
	printf("find room");

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

			send(sock, &y, sizeof(y), 0);

			system("cls");

			switch (y) {
			case CREATE: {
				msg_int = CreateRoom(sock);
				if (msg_int = -1) {
					goto END_DEFAULTPLAYER;
				}
				break;
			}

			case FIND: {
				FindRoom(sock);
				break;
			}

			}
			break;
		}
		}
	}

	recv(sock, &msg_int, sizeof(msg_int), 0);

	if (msg_int == 1) {
		FirstPlayer(sock);
	}

	else {
		SecondPlayer(sock);
	}

END_DEFAULTPLAYER:
	return;
}

int CreateRoom(SOCKET sock)
{
	char msg_char[MAX_MSG_LEN] = "";
	int msg_int = 1;

	while (msg_int) {
		printf("방 이름 : ");
		scanf("%s", &msg_char);
		send(sock, msg_char, sizeof(msg_char), 0);
		recv(sock, &msg_int, sizeof(msg_int), 0);
		if (msg_int == -1) {
			goto END_CREATEROOM;
		}

		else if (msg_int == 1) {
			system("cls");
			printf("중복되는 방 이름이 있습니다.\n");
			printf("다른 방 이름을 입력해 주세요.\n");
			system("pause");
			system("cls");
		}
	}
	printf("방 비밀번호 : ");
	scanf("%d", &msg_int);
	send(sock, &msg_int, sizeof(msg_int), 0);

	recv(sock, &msg_int, sizeof(msg_int), 0);

END_CREATEROOM:
	return msg_int;
}

int FindRoom(SOCKET sock)
{
	int msg_int;

	recv(sock, &msg_int, sizeof(msg_int), 0);

	if (msg_int == 0) {
		printf("현재 개설되어있는 방이 없습니다.");
	}

	for (int i = 0; i < msg_int; i++) {
		printf("방 이름 : ");
	}
}

void FirstPlayer(SOCKET sock)
{

}

void SecondPlayer(SOCKET sock)
{

}

void LoadGame(SOCKET sock)
{
	int num_saves;
	int msg_int;

	recv(sock, &num_saves, sizeof(num_saves), 0);

	if (num_saves == 0) {
		printf("불러올 수 있는 게임 정보가 없습니다. \n");
	}

	else {
		for (int i = 0; i < num_saves; ++i) {
			printf("%d번", i);

			recv(sock, &msg_int, sizeof(msg_int), 0);
			printf("챕터 : %d \n", msg_int);

			recv(sock, &msg_int, sizeof(msg_int), 0);
			printf("스테이지 : %d \n \n", msg_int);
		}

		printf("불러들일 게임 정보 선택 : ");
		scanf("%d", &msg_int);
		send(sock, &msg_int, sizeof(msg_int), 0);
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