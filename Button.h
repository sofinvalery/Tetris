#pragma once

#include <SDL.h>
#include "Texture.h"

class Button : public Texture {
public:
	Button();
	void Check(SDL_Event* event) override;
	bool is_Pressed() override;

private:
	bool pressed;
};