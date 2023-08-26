#pragma warning(disable:4996)

#include <WinSock2.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "story.h"
#include "system.h"

int rogin_player_num;

void DefaultPlayer(SOCKET);
int CreateRoom(SOCKET);
int FindRoom(SOCKET);
void WaitRoom(SOCKET);
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
	int msg_int = 1;

	x = 2;
	y = 0;

	MoveCursor(x - 2, y);
	printf("> create room");

	MoveCursor(x, y + 2);
	printf("find room");

	while (msg_int > 0) {

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
			if (y < 2) {
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
				if (msg_int == -1) {
					return;
				}
				break;
			}

			case FIND: {
				msg_int = FindRoom(sock);
				if (msg_int == -1) {
					return;
				}
				break;
			}
			}
			WaitRoom(sock);
			break;
		}
		}
	}
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
			return msg_int;
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

	recv(sock, &rogin_player_num, sizeof(rogin_player_num), 0);

	return 0;
}

int FindRoom(SOCKET sock)
{
	char msg_char[MAX_MSG_LEN] = "";
	int msg_int;

	recv(sock, &msg_int, sizeof(msg_int), 0);

	if (msg_int == 0) {
		printf("���� �����Ǿ��ִ� ���� �����ϴ�. \n");
		system("pause");
		return -1;
	}

	else {
		for (int i = 0; i < msg_int; i++) {
			recv(sock, msg_char, sizeof(msg_char), 0);
			printf("%d. �� �̸� : %s \n \n", i + 1, msg_char);
		}
	}

	printf("�� ��ȣ �Է� : ");
	scanf("%d", &msg_int);
	msg_int -= 1;

	send(sock, &msg_int, sizeof(msg_int), 0);

	if (msg_int < 0) {
		return -1;
	}

	recv(sock, &msg_int, sizeof(msg_int), 0);

	if (msg_int == 1) {
		system("cls");
		printf("���� ���� �̹� ���� ��ȣ�� �÷��̾ �ֽ��ϴ�. \n");
		system("pause");
		return -1;
	}

	printf("�� ��й�ȣ : ");
	scanf("%d", &msg_int);

	send(sock, &msg_int, sizeof(msg_int), 0);
	recv(sock, &msg_int, sizeof(msg_int), 0);

	if (msg_int == 0) {
		system("cls");
		printf("��й�ȣ�� �ٸ��ϴ�. \n");
		system("pause");
		return -1;
	}

	recv(sock, &rogin_player_num, sizeof(rogin_player_num), 0);

	return 0;
}

void WaitRoom(SOCKET sock)
{
	int msg_int;

	system("cls");
	printf("�÷��̾ ��ٸ��� �� 1/2");

	recv(sock, &msg_int, sizeof(msg_int), 0);
	printf("test.%d\n", msg_int);
	system("pause");

	send(sock, &rogin_player_num, sizeof(rogin_player_num), 0);
	recv(sock, &msg_int, sizeof(msg_int), 0);

	system("cls");

	if (msg_int == 1) {
		Chapter1_Player1(sock);
	}

	else {
		Chapter1_Player2(sock);
	}
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