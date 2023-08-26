#include <winsock2.h>

#include "game.h"
#include "story.h"
#include "system.h"

void Menu(SOCKET sock)
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

			}

			case CLUE: {

			}

			case OPTION_MENU: {
				y = Option(sock);

				if (y == 1) {
					return 0;
				}
				break;
			}

			case BACK_MENU: {

			}

			case EXIT_MENU: {

			}

			}
		}
		}
	}
}

void Chapter1_Player1(SOCKET sock)
{
	int x = 2;
	int y = 2;
	int key = 0;
	int explore = 0;
	int investigate = 0;

	while (explore < 1 || investigate < 1) {

		printf("ģ���� �Բ� ������ ��԰� ������ ���ڸ��� �츮�� ���� ���� �����.");
		printf("�ῡ�� ����� ������ �ѷ����� ������ �ƴ� �ٸ� ���ó�� ������.");

		MoveCursor(x - 2, y);
		printf("> ���� �ѷ�����");

		MoveCursor(x, y + 2);
		printf("�� ����");

		MoveCursor(x, y + 4);
		printf("�޴�");

		while (key != 4) {
			int key = ControlKey();

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
					printf("���� �ణ ������ ������ ��ȭ�Ⱑ ���̰� �ƹ��� �Ҹ��� �鸮�� �ʴ´�.");
					printf("�� 3���� ���δ�.");
					system("pause");
					explore++;
					break;
				}

				case INVESTIGATE: {
					printf("������, ����, ��ø�� �ִ�.");
					printf("������, ����, ��ø ȹ��");
					system("pause");
					investigate++;
					break;
				}

				case MENU_STAGE1: {
					Menu(sock);
					break;
				}

				}
			}

			}

		}
	}
}

void Chapter1_Player2(SOCKET sock)
{

}