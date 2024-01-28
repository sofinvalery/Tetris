#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include "Texture.h"
#include "Globals.h"

using namespace std;

class TextBox : public Texture {
public:
	TextBox();
	~TextBox();

	string Get_Input() override { return input; }
	void Set_Input(string text) override { input = text; }

private:
	TTF_Font* text_font;
	SDL_Surface* text_surface;
	SDL_Texture* text_texture;
	SDL_Renderer* mRenderer;

	int mX;
	int mY;
	int mWidth;
	int mHeight;

	string input = " ";
};