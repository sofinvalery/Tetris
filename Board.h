#pragma once

#include <SDL.h>
#include <random>
#include <time.h>
#include <iostream>
#include "Globals.h"

class Board {
public:
	Board();

	void Draw_Board();
	int Tick();
	void Set_Renderer(SDL_Renderer* renderer);
	void Handle_event(SDL_Event* event);
	bool Check();
	int Get_Score() { return score; }

private:
	SDL_Renderer* board_Renderer;

	int current, next = 2;
	Uint32 timer = 0, delay = 100000;
	Uint32 time = SDL_GetTicks();

	int board[20][10] = { 0 };

	struct point {
		int x;
		int y;
	} a[4], b[4], c[4];

	int figures[7][4] = {
		1, 3, 5, 7,
		2, 4, 5, 7,
		3, 5, 4, 6,
		3, 5, 4, 7,
		2, 3, 5, 7,
		3, 5, 7, 6,
		2, 3, 4, 5
	};

	int dx = 0;
	bool rotate = false;

	int score = 0;
};