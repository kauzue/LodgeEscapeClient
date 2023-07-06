#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "system.h"

int LoginMenu()
{
	int x = 2;
	int y = 2;

	MoveCursor(x - 2, y - 2);
	printf("로그인 메뉴 \n \n");

	MoveCursor(x - 2, y);
	printf("> 회원가입 \n");

	MoveCursor(x, y + 1);
	printf("로그인 \n");

    while (true) {
        int key = ControlKey();

        switch (key) {
        case UP:
            if (y > 2) {
                MoveCursor(x - 2, y);
                printf(" ");
                MoveCursor(x - 2, --y);
                printf(">");
            }
            break;

        case DOWN:
            if (y < 3) {
                MoveCursor(x - 2, y);
                printf(" ");

                MoveCursor(x - 2, ++y);
                printf(">");
            }
            break;

        case ENTER:
		return y - 2;
        	break;
        }
    }
}
