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
		printf("�ҷ��� �� �ִ� ���� ������ �����ϴ�. \n");
	}

	else {
		for (msg_int; msg_int > 0; --msg_int) {
			recv(sock, &msg_int, sizeof(msg_int), 0);
			printf("é�� : %d \n", msg_int);

			recv(sock, &msg_int, sizeof(msg_int), 0);
			printf("�������� : %d \n \n", msg_int);
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