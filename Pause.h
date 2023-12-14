#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Globals.h"
#include "Scene.h"
#include "Texture.h"
#include "Button.h"

class Pause : public Scene {
public:
	Pause();

	void Draw() override;
	int Handle_event(SDL_Event* event) override;
	void Init_Pause() override;

private:
	TTF_Font* title_font;
	TTF_Font* information_font;

	Texture** texture_array;
};