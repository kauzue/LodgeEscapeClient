#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "system.h"

void LoginMenu()
{
	int x = 2;
	int y = 2;

	MoveCursor(x - 2, y - 2);
	printf("�α��� �޴� \n \n");

	MoveCursor(x - 2, y);
	printf("> ȸ������ \n");

	MoveCursor(x, y + 1);
	printf("�α��� \n");

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
            break;
        }
    }
}