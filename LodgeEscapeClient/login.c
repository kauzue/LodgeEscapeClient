<<<<<<< HEAD
#pragma warning(disable:4996)

#include <stdio.h>
#include <WinSock2.h>
#include <stdbool.h>

#include "login.h"
#include "system.h"

int LoginMenu(SOCKET sock)
{
    int x = 2;
    int y = 2;
    int players_num;

    char msg_char[MAX_MSG_LEN] = "";

    MoveCursor(x - 2, y - 2);
    printf("�α��� �޴� \n \n");

    MoveCursor(x - 2, y);
    printf("> ȸ������ \n");

    MoveCursor(x, y + 1);
    printf("�α��� \n");

    MoveCursor(x, y + 2);
    printf("���� \n");

    while (true) {
        int key = ControlKey();

        switch (key) {
        case UP: {
            if (y > 2) {
                MoveCursor(x - 2, y);
                printf(" ");
                MoveCursor(x - 2, --y);
                printf(">");
            }
            break;
        }

        case DOWN: {
            if (y < 4) {
                MoveCursor(x - 2, y);
                printf(" ");

                MoveCursor(x - 2, ++y);
                printf(">");
            }
            break;
        }

        case ENTER: {
            y -= 2;
            system("cls");
            send(sock, &y, sizeof(y), 0);

            switch (y) {
            case SIGNUP: {
                int same = 0;

                do {
                    printf("ID : ");
                    scanf("%s", &msg_char);
                    send(sock, msg_char, MAX_MSG_LEN, 0);
                    recv(sock, &players_num, sizeof(players_num), 0);

                    for (int i = 0; i < players_num; i++) {
                        recv(sock, &same, sizeof(same), 0);
                        if (same != 0) {
                            system("cls");
                            printf("�ߺ��Ǵ� ���̵��Դϴ�. \n");
                            printf("�ٽ� �Է��� �ּ���. \n");
                            system("pause");
                            system("cls");
                        }
                    }

                } while (same);

                printf("Password : ");
                scanf("%s", &msg_char);
                send(sock, msg_char, MAX_MSG_LEN, 0);

                do {
                    printf("Player Number : ");
                    scanf("%d", &players_num);
                    send(sock, &players_num, sizeof(players_num), 0);
                    recv(sock, &same, sizeof(same), 0);
                    if (same != 0) {
                        system("cls");
                        printf("1�� 2�� �� �ϳ��� ���ڸ� �Է��� �ּ���.");
                        system("pause");
                        system("cls");
                    }
                } while (same);
                
                break;
            }

            case LOGIN: {
                printf("ID : ");
                scanf("%s", &msg_char);
                send(sock, msg_char, MAX_MSG_LEN, 0);

                printf("PassWord : ");
                scanf("%s", &msg_char);
                send(sock, msg_char, MAX_MSG_LEN, 0);

                break;
            }

            case ESC: {
                return y - 2;
            }
            }
            break;
        }
        }
    }
=======
#pragma warning(disable:4996)

#include <stdio.h>
#include <WinSock2.h>
#include <stdbool.h>

#include "login.h"
#include "system.h"

int LoginMenu(SOCKET sock)
{
    int x = 2;
    int y = 2;
    int players_num;

    char msg_char[MAX_MSG_LEN] = "";

    MoveCursor(x - 2, y - 2);
    printf("�α��� �޴� \n \n");

    MoveCursor(x - 2, y);
    printf("> ȸ������ \n");

    MoveCursor(x, y + 1);
    printf("�α��� \n");

    MoveCursor(x, y + 2);
    printf("���� \n");

    while (true) {
        int key = ControlKey();

        switch (key) {
        case UP: {
            if (y > 2) {
                MoveCursor(x - 2, y);
                printf(" ");
                MoveCursor(x - 2, --y);
                printf(">");
            }
            break;
        }

        case DOWN: {
            if (y < 4) {
                MoveCursor(x - 2, y);
                printf(" ");

                MoveCursor(x - 2, ++y);
                printf(">");
            }
            break;
        }

        case ENTER: {
            y -= 2;
            system("cls");
            send(sock, &y, sizeof(y), 0);

            switch (y) {
            case SIGNUP: {
                int same = 0;

                do {
                    printf("ID : ");
                    scanf("%s", &msg_char);
                    send(sock, msg_char, MAX_MSG_LEN, 0);
                    recv(sock, &players_num, sizeof(players_num), 0);

                    for (int i = 0; i < players_num; i++) {
                        recv(sock, &same, sizeof(same), 0);
                        if (same != 0) {
                            system("cls");
                            printf("�ߺ��Ǵ� ���̵��Դϴ�. \n");
                            printf("�ٽ� �Է��� �ּ���. \n");
                            system("pause");
                            system("cls");
                        }
                    }

                } while (same);

                printf("Password : ");
                scanf("%s", &msg_char);
                send(sock, msg_char, MAX_MSG_LEN, 0);

                do {
                    printf("Player Number : ");
                    scanf("%d", &players_num);
                    send(sock, &players_num, sizeof(players_num), 0);
                    recv(sock, &same, sizeof(same), 0);
                    if (same != 0) {
                        system("cls");
                        printf("1�� 2�� �� �ϳ��� ���ڸ� �Է��� �ּ���.");
                        system("pause");
                        system("cls");
                    }
                } while (same);
            }

            case LOGIN: {
                printf("ID : ");
                scanf("%s", &msg_char);
                send(sock, msg_char, MAX_MSG_LEN, 0);

                printf("PassWord : ");
                scanf("%s", &msg_char);
                send(sock, msg_char, MAX_MSG_LEN, 0);
            }

            case ESC: {
                return y - 2;
            }
            }
            break;
        }
        }
    }
>>>>>>> 3602cd7825d1514826032536e74c594105502df0
}