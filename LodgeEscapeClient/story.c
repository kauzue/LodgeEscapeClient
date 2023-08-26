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

		printf("친구와 함께 여관에 놀러왔고 여관에 들어서자마자 우리는 졸려 잠이 들었다.");
		printf("잠에서 깨어나서 주위를 둘러보니 여관이 아닌 다른 장소처럼 보였다.");

		MoveCursor(x - 2, y);
		printf("> 주위 둘러보기");

		MoveCursor(x, y + 2);
		printf("몸 수색");

		MoveCursor(x, y + 4);
		printf("메뉴");

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
					printf("불이 약간 들어오는 전구와 전화기가 보이고 아무런 소리도 들리지 않는다.");
					printf("문 3개가 보인다.");
					system("pause");
					explore++;
					break;
				}

				case INVESTIGATE: {
					printf("손전등, 지갑, 수첩이 있다.");
					printf("손전등, 지갑, 수첩 획득");
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