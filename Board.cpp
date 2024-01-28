#include "Board.h"

Board::Board() {
}

void Board::Set_Renderer(SDL_Renderer* renderer) {
	board_Renderer = renderer;
}

void Board::Draw_Board() {
	SDL_Rect cell;

	SDL_SetRenderDrawColor(board_Renderer, 255, 255, 255, 255);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			cell = { SCREEN_WIDTH / 2 - 175 + i * SCALE, SCREEN_HEIGHT / 2 - 350 + j * SCALE, SCALE, SCALE };
			SDL_RenderDrawRect(board_Renderer, &cell);
		}
	}

	for (int i = 0; i < 4; i++) {
		c[i].x = figures[next][i] % 2;
		c[i].y = figures[next][i] / 2;
	}

	for (int i = 0; i < 4; i++) {
		cell = { 3 * SCREEN_WIDTH / 4 + 100 + c[i].x * SCALE, SCREEN_HEIGHT / 4 + 150 + c[i].y * SCALE, SCALE, SCALE };
		SDL_SetRenderDrawColor(board_Renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(board_Renderer, &cell);
		SDL_SetRenderDrawColor(board_Renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(board_Renderer, &cell);
	}
}

bool Board::Check() {
	for (int i = 0; i < 4; i++) {
		if (a[i].x < 0 || a[i].x >= 10 || a[i].y >= 20) {
			return false;
		}
		else if (board[a[i].y][a[i].x]) {
			return false;
		}
	}
	return true;
}

int Board::Tick() {
	SDL_Rect cell;
	std::random_device rd;
	std::mt19937 gen(rd());

	timer += time;
	time = SDL_GetTicks();

	for (int i = 0; i < 4; i++) {
		b[i] = a[i];
		a[i].x += dx;
	}

	if (!Check()) {
		for (int i = 0; i < 4; i++) {
			a[i] = b[i];
		}
	}

	if (rotate) {
		point p = a[1];
		for (int i = 0; i < 4; i++) {
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;

			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}

		if (!Check()) {
			for (int i = 0; i < 4; i++) {
				a[i] = b[i];
			}
		}
	}

	if (timer > delay) {
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].y += 1;
		}

		if (!Check()) {
			for (int i = 0; i < 4; i++) {
				board[b[i].y][b[i].x] = 1;
			}

			current = next;
			next = gen() % 7;
			for (int i = 0; i < 4; i++) {
				a[i].x = figures[current][i] % 2 + 4;
				a[i].y = figures[current][i] / 2;
			}
		}
		timer = 0;
	}

	int k = 20 - 1;
	for (int i = 20 - 1; i > 0; i--) {
		int count = 0;
		for (int j = 0; j < 10; j++) {
			if (board[i][j]) count++;
			board[k][j] = board[i][j];
		}
		if (count < 10) {
			k--;
		}
		else {
			score += 100;
		}
	}

	dx = 0;
	rotate = false;
	delay = 100000;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j] == 0) continue;
			cell = { SCREEN_WIDTH / 2 - 175 + j * SCALE, SCREEN_HEIGHT / 2 - 350 + i * SCALE, SCALE, SCALE };
			SDL_SetRenderDrawColor(board_Renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(board_Renderer, &cell);
			SDL_SetRenderDrawColor(board_Renderer, 0, 0, 0, 255);
			SDL_RenderDrawRect(board_Renderer, &cell);
		}
	}

	for (int i = 0; i < 4; i++) {
		cell = { SCREEN_WIDTH / 2 - 175 + a[i].x * SCALE, SCREEN_HEIGHT / 2 - 350 + a[i].y * SCALE, SCALE, SCALE };
		SDL_SetRenderDrawColor(board_Renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(board_Renderer, &cell);
		SDL_SetRenderDrawColor(board_Renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(board_Renderer, &cell);
	}

	for (int j = 0; j < 10; j++) {
		if (board[1][j]) {
			std::cout << "Game over" << std::endl;
			return 0;
		}
	}
	return 1;
}

void Board::Handle_event(SDL_Event* event) {
	switch (event->key.keysym.sym) {
	case SDLK_UP:
		rotate = true;
		break;
	case SDLK_RIGHT:
		dx = 1;
		break;
	case SDLK_LEFT:
		dx = -1;
		break;
	case SDLK_DOWN:
		delay = 10000;
		break;
	}
}