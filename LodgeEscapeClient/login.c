#pragma warning(disable:4996)

#include <stdio.h>
#include <WinSock2.h>
#include <stdbool.h>

#include "login.h"
#include "system.h"

int LoginMenu(SOCKET sock)
{
    int x;
    int y = 2;
    int msg_int;
    int players_num;

    char msg_char[MAX_MSG_LEN] = "";

    while (y != 11) {
        x = 2;
        y = 2;

        MoveCursor(x - 2, y - 2);
        printf("로그인 메뉴 \n \n");

        MoveCursor(x - 2, y);
        printf("> 회원가입 \n");

        MoveCursor(x, y + 1);
        printf("로그인 \n");

        MoveCursor(x, y + 2);
        printf("종료 \n");

        while ((y > 9) == 0) {
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
                    int id;

                    do {
                        id = 0;
                        printf("ID : ");
                        scanf("%s", &msg_char);
                        send(sock, msg_char, MAX_MSG_LEN, 0);
                        if (!strcmp(msg_char, "0")) {
                            return 0;
                        }

                        recv(sock, &same, sizeof(same), 0);
                        if (same != 0) {
                            system("cls");
                            printf("중복되는 아이디입니다. \n");
                            printf("다시 입력해 주세요. \n");
                            system("pause");
                            system("cls");
                            id = 1;
                        }

                    } while (id);

                    printf("Password : ");
                    scanf("%s", &msg_char);
                    send(sock, msg_char, MAX_MSG_LEN, 0);
                    if (!strcmp(msg_char, "0")) {
                        return 0;
                    }

                    do {
                        printf("Player Number : ");
                        scanf("%d", &players_num);
                        send(sock, &players_num, sizeof(players_num), 0);
                        if (players_num == 0) {
                            return 0;
                        }

                        if (players_num != 1 && players_num != 2) {
                            system("cls");
                            printf("1과 2의 중 하나의 숫자를 입력해 주세요.");
                            system("pause");
                            system("cls");
                            same++;
                        }

                        send(sock, &same, sizeof(same), 0);

                    } while (same);

                    system("cls");
                    break;
                }

                case LOGIN: {
                    do {
                        printf("ID : ");
                        scanf("%s", &msg_char);
                        send(sock, msg_char, MAX_MSG_LEN, 0);
                        if (!strcmp(msg_char, "0")) {
                            return 0;
                        }

                        printf("PassWord : ");
                        scanf("%s", &msg_char);
                        send(sock, msg_char, MAX_MSG_LEN, 0);
                        if (!strcmp(msg_char, "0")) {
                            return 0;
                        }

                        recv(sock, &msg_int, sizeof(msg_int), 0);

                        if (msg_int == 0) {
                            system("cls");
                            printf("아이디 혹은 비밀번호가 일치하지 않습니다. \n");
                            printf("다시 입력해주세요 \n");
                            system("pause");
                            system("cls");
                        }

                        else {
                            system("cls");
                        }
                    } while (!msg_int);

                    break;
                }

                case ESC: {
                    return 0;
                }
                }
                y += 10;
            }
            }
        }
    }
    return msg_int;
}