#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Globals.h"
#include "Scene.h"
#include "Texture.h"
#include "Button.h"

class Menu : public Scene {
public:
	Menu();

	void Draw() override;
	int Handle_event(SDL_Event* event) override;
	void Init_menu() override;
private:
	TTF_Font* title_font;
	TTF_Font* instructions_font;
	TTF_Font* author_font;

	Texture** texture_array;
};