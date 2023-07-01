#pragma once

enum KEY { UP, DOWN, LEFT, RIGHT, ENTER };

void InitSystem();
int ControlKey();
void MoveCursor(int x, int y);