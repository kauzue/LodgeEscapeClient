#pragma once

#define NUM_MAX_ENDING 5

enum MAIN { START_GAME, LOAD_GAME, OPTION, ENDING, EXIT };
enum ROOM {CREATE, FIND};
enum OPTION { LOGIN_DATA };

int StartGame(SOCKET);
void FirstPlayer(SOCKET);
void SecondPlayer(SOCKET);