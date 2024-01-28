#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Globals.h"
#include "Scene.h"
#include "Texture.h"
#include "Button.h"

class Info : public Scene {
public:
	Info();

	void Draw() override;
	int Handle_event(SDL_Event* event) override;
	void Init_info() override;

private:
	TTF_Font* title_font;
	TTF_Font* information_font;
	TTF_Font* info_font;

	Texture** texture_array;
};