#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Globals.h"
#include "Scene.h"
#include "Texture.h"
#include "Button.h"

class Scores : public Scene {
public:
	Scores();

	void Draw() override;
	int Handle_event(SDL_Event* event) override;
	void Init_scores() override;

private:
	TTF_Font* title_font;
	TTF_Font* score_font;

	Texture** texture_array;
};