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
		printf("�� �̸� : ");
		scanf("%s", &msg_char);
		send(sock, msg_char, sizeof(msg_char), 0);
		recv(sock, &msg_int, sizeof(msg_int), 0);
		if (msg_int == -1) {
			goto END_CREATEROOM;
		}

		else if (msg_int == 1) {
			system("cls");
			printf("�ߺ��Ǵ� �� �̸��� �ֽ��ϴ�.\n");
			printf("�ٸ� �� �̸��� �Է��� �ּ���.\n");
			system("pause");
			system("cls");
		}
	}
	printf("�� ��й�ȣ : ");
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
		printf("���� �����Ǿ��ִ� ���� �����ϴ�.");
	}

	for (int i = 0; i < msg_int; i++) {
		printf("�� �̸� : ");
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
		printf("�ҷ��� �� �ִ� ���� ������ �����ϴ�. \n");
	}

	else {
		for (int i = 0; i < num_saves; ++i) {
			printf("%d��", i);

			recv(sock, &msg_int, sizeof(msg_int), 0);
			printf("é�� : %d \n", msg_int);

			recv(sock, &msg_int, sizeof(msg_int), 0);
			printf("�������� : %d \n \n", msg_int);
		}

		printf("�ҷ����� ���� ���� ���� : ");
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
	printf("> �α��� ����");
	
	MoveCursor(x, y + 2);
	printf("�α׾ƿ�");

	MoveCursor(x, y + 4);
	printf("�ǵ��ư���");

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
				printf("��й�ȣ : %s \n", msg_char);

				recv(sock, &msg_int, sizeof(msg_int), 0);
				printf("�÷��̾� ��ȣ : %d \n", msg_int);

				recv(sock, &msg_int, sizeof(msg_int), 0);
				printf("�߰��� ���� : %d�� \n", msg_int);

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

		printf("���� ��ȣ : %d \n", i + 1);

		recv(sock, &msg_int, sizeof(msg_int), 0);

		if (msg_int == 1) {
			recv(sock, msg_char, MAX_MSG_LEN, 0);

			printf("���� : %s \n", msg_char);
		}

		else {
			printf("���� : ���� �߰����� ���� \n \n");
		}
		
	}

	system("pause");
}