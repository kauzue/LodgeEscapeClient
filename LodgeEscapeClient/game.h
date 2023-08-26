#pragma once

#define NUM_MAX_ENDING 5
#define NUM_MAX_PLAYERS 100

typedef struct player {
	int rogin_player_number;
}player_t;

enum MAIN { START_GAME, LOAD_GAME, OPTION, ENDING, EXIT };
enum ROOM {CREATE, FIND};
enum OPTION { LOGIN_DATA };

int StartGame(SOCKET);