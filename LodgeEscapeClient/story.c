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
	printf("> 아이템");

	MoveCursor(x, y + 2);
	printf("단서");

	MoveCursor(x, y + 4);
	printf("옵션");

	MoveCursor(x, y + 6);
	printf("이전");

	MoveCursor(x, y + 8);
	printf("종료");

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
					printf("현재 발견한 아이템이 없습니다. \n");
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
					printf("현재 발견한 단서가 없습니다. \n");
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
	printf("> 로그인 정보");

	MoveCursor(x, y + 2);
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

void Chapter1_Player1(SOCKET sock)
{
	int menu = 1;
	int explore = 0;
	int investigate = 0;

	while (explore < 1 || investigate < 1) {

		int x = 2;
		int y = 2;
		int key = 0;

		printf("친구와 함께 여관에 놀러왔고 여관에 들어서자마자 우리는 졸려 잠이 들었다.");
		printf("잠에서 깨어나서 주위를 둘러보니 여관이 아닌 다른 장소처럼 보였다.");

		MoveCursor(x - 2, y);
		printf("> 주위 둘러보기");

		MoveCursor(x, y + 2);
		printf("몸 수색");

		MoveCursor(x, y + 4);
		printf("메뉴");

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
					printf("불이 약간 들어오는 전구와 전화기가 보이고 아무런 소리도 들리지 않는다. \n");
					printf("문 3개가 보인다.");
					system("pause");
					explore++;
					break;
				}

				case INVESTIGATE: {
					printf("손전등, 지갑, 수첩이 있다. \n");
					printf("손전등, 지갑, 수첩 획득 \n");
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

							printf("현재 기다리는 플레이어 1/2");

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

		printf("친구와 함께 여관에 놀러왔고 여관에 들어서자마자 우리는 졸려 잠이 들었다.");
		printf("잠에서 깨어나서 주위를 둘러보니 친구가 사라져있었다.");

		MoveCursor(x - 2, y);
		printf("> 집 안을 조사");

		MoveCursor(x, y + 2);
		printf("몸 수색");

		MoveCursor(x, y + 4);
		printf("메뉴");

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
					printf("촛불만이 빛을 비추고 있는 여관 안에 있는 것 같다. \n");
					printf("밖에는 어둡고 비가 오며 창문과 출입구는 모두 잠겨있어 나가기 어려울 것 같다. \n");
					printf("안에는 전화기와 다른 방으로 연결된 문 5개만 보인다. \n");
					system("pause");
					explore++;
					break;
				}

				case INVESTIGATE: {
					printf("지갑 외에는 아무런 단서도 없었다. \n");
					printf("지갑 획득 \n");
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

							printf("현재 기다리는 플레이어 1/2");

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