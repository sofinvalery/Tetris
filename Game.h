#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include "Globals.h"
#include "Scene.h"
#include "Texture.h"
#include "Button.h"
#include "Board.h"
#include "Pause.h"
#include "TextBox.h"

class Game : public Scene {
public:
	Game();

	void Draw() override;
	int Handle_event(SDL_Event* event) override;
	void Init_game() override;

private:
	TTF_Font* title_font;
	TTF_Font* info_font;
	TTF_Font* information_font;

	Texture** texture_array;

	Board* current_board;
	int user_score;

	bool flag = false;
};
