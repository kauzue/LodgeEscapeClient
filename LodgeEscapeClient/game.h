#pragma once

enum MAIN { START_GAME, LOAD_GAME, OPTION, EXIT };

void StartGame(SOCKET, int);
void FirstPlayer();
void SecondPlayer();