#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Globals.h"

class Window {
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	TTF_Font* mFont;

public:
	Window();
	virtual ~Window();

	void Clear();
	void Render();

	SDL_Renderer* get_Renderer();

	virtual void Draw() {}
	virtual int Handle_event(SDL_Event* event) { return -1; }
};