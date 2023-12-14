#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include "Globals.h"
#include "Scene.h"
#include "Texture.h"
#include "Button.h"
#include "TextBox.h"

class Input_User : public Scene {
public:
	Input_User();

	void Draw() override;
	int Handle_event(SDL_Event* event) override;
	void Init_Input_User() override;

private:
	TTF_Font* title_font;
	TTF_Font* information_font;

	Texture** texture_array;
};