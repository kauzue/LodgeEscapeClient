#pragma once

#define MAX_MSG_LEN 256

enum KEY { UP, DOWN, LEFT, RIGHT, ENTER };

void InitSystem();
int ControlKey();
void MoveCursor(int x, int y);