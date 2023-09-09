#include <winsock2.h>
#include <stdbool.h>

#include "game.h"
#include "story.h"
#include "system.h"

int Option_Story(SOCKET);
void Chapter2_Player1(SOCKET sock);
void Chapter2_Player2(SOCKET sock);
void End_Story(SOCKET sock);

int Menu(SOCKET sock)
{
	int x = 2;
	int y = 0;
	int key = 0;

	MoveCursor(x - 2, y);
	printf("> ������");

	MoveCursor(x, y + 2);
	printf("�ܼ�");

	MoveCursor(x, y + 4);
	printf("�ɼ�");

	MoveCursor(x, y + 6);
	printf("����");

	MoveCursor(x, y + 8);
	printf("����");

	while (key < 6) {
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
			case ITEM: {
				int num_items;
				char name_item[MAX_MSG_LEN] = "";
				char information_item[MAX_MSG_LEN] = "";

				recv(sock, &num_items, sizeof(num_items), 0);

				if (num_items == 0) {
					printf("���� �߰��� �������� �����ϴ�. \n");
					system("pause");
					return 0;
				}

				for (int i = 0; i < num_items; i++) {
					recv(sock, name_item, sizeof(name_item), 0);
					recv(sock, information_item, sizeof(information_item), 0);

					printf("%d. %s \n \n", i + 1, name_item);
					printf("%s \n \n \n", information_item);
				}
				system("pause");
				return 0;
			}

			case CLUE: {
				int num_clues;
				char name_clue[MAX_MSG_LEN] = "";
				char information_clue[MAX_MSG_LEN] = "";

				recv(sock, &num_clues, sizeof(num_clues), 0);

				if (num_clues == 0) {
					printf("���� �߰��� �ܼ��� �����ϴ�. \n");
					system("pause");
					return 0;
				}

				for (int i = 0; i < num_clues; i++) {
					recv(sock, name_clue, sizeof(name_clue), 0);
					recv(sock, information_clue, sizeof(information_clue), 0);

					printf("%d. %s \n \n", i + 1, name_clue);
					printf("%s \n", information_clue);
				}
				system("pause");
				return 0;
			}

			case OPTION_MENU: {
				y = Option_Story(sock);

				return 0;
				break;
			}

			case BACK_MENU: {
				return 1;
			}

			case EXIT_MENU: {
				return -1;
			}

			}
		}
		}
	}
}

int Option_Story(SOCKET sock)
{
	char msg_char[MAX_MSG_LEN] = "";
	int msg_int;
	int x, y;

	x = 2;
	y = 0;

	MoveCursor(x - 2, y);
	printf("> �α��� ����");

	MoveCursor(x, y + 2);
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

void Chapter1_Player1(SOCKET sock)
{
	int menu = 1;
	int explore = 0;
	int investigate = 0;

	while (explore < 1 || investigate < 1) {

		int x = 2;
		int y = 2;
		int key = 0;

		printf("ģ���� �Բ� ������ ��԰� ������ ���ڸ��� �츮�� ���� ���� �����.");
		printf("�ῡ�� ����� ������ �ѷ����� ������ �ƴ� �ٸ� ���ó�� ������.");

		MoveCursor(x - 2, y);
		printf("> ���� �ѷ�����");

		MoveCursor(x, y + 2);
		printf("�� ����");

		MoveCursor(x, y + 4);
		printf("�޴�");

		while (key != 4) {
			key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 2) {
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
				y = y / 2 - 1;

				system("cls");

				send(sock, &y, sizeof(y), 0);

				switch (y) {

				case EXPLORE: {
					printf("���� �ణ ������ ������ ��ȭ�Ⱑ ���̰� �ƹ��� �Ҹ��� �鸮�� �ʴ´�. \n");
					printf("�� 3���� ���δ�.");
					system("pause");
					explore++;
					break;
				}

				case INVESTIGATE: {
					printf("������, ����, ��ø�� �ִ�. \n");
					printf("������, ����, ��ø ȹ�� \n");
					system("pause");
					investigate++;
					break;
				}

				case MENU_STAGE1: {
					do {
						system("cls");
						menu = Menu(sock);

						if (menu == -1) {
							int msg_int;

							printf("���� ��ٸ��� �÷��̾� 1/2");

							recv(sock, &msg_int, sizeof(msg_int), 0);
							if (msg_int == 2) {
								return;
							}
						}

					} while (menu <= 0);
					break;
				}

				}
			}

			}

		}
		system("cls");
	}

	Chapter2_Player1(sock);

}

void Chapter1_Player2(SOCKET sock)
{
	int menu = 1;
	int explore = 0;
	int investigate = 0;

	while (explore < 1 || investigate < 1) {

		int x = 2;
		int y = 2;
		int key = 0;

		printf("ģ���� �Բ� ������ ��԰� ������ ���ڸ��� �츮�� ���� ���� �����.");
		printf("�ῡ�� ����� ������ �ѷ����� ģ���� ������־���.");

		MoveCursor(x - 2, y);
		printf("> �� ���� ����");

		MoveCursor(x, y + 2);
		printf("�� ����");

		MoveCursor(x, y + 4);
		printf("�޴�");

		while (key != 4) {
			key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 2) {
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
				y = y / 2 - 1;

				system("cls");

				send(sock, &y, sizeof(y), 0);

				switch (y) {

				case EXPLORE: {
					printf("�кҸ��� ���� ���߰� �ִ� ���� �ȿ� �ִ� �� ����. \n");
					printf("�ۿ��� ��Ӱ� �� ���� â���� ���Ա��� ��� ����־� ������ ����� �� ����. \n");
					printf("�ȿ��� ��ȭ��� �ٸ� ������ ����� �� 5���� ���δ�. \n");
					system("pause");
					explore++;
					break;
				}

				case INVESTIGATE: {
					printf("���� �ܿ��� �ƹ��� �ܼ��� ������. \n");
					printf("���� ȹ�� \n");
					system("pause");
					investigate++;
					break;
				}

				case MENU_STAGE1: {
					do {
						system("cls");
						menu = Menu(sock);

						if (menu == -1) {
							int msg_int;

							printf("���� ��ٸ��� �÷��̾� 1/2");

							recv(sock, &msg_int, sizeof(msg_int), 0);
							if (msg_int == 2) {
								return;
							}
						}

					} while (menu <= 0);
					break;
				}

				}
			}

			}

		}
		system("cls");
	}

	Chapter2_Player1(sock);
}

void Chapter2_Player1(SOCKET sock)
{

}

void Chapter2_Player2(SOCKET sock)
{

}

void End_Story(SOCKET sock)
{

}