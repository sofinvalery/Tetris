#include "Button.h"

Button::Button() : pressed(false), Texture() {}

void Button::Check(SDL_Event* event) {
	switch (event->type) {
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT) {
			int mx, my;
			mx = event->button.x;
			my = event->button.y;

			if (mx >= Get_X() && mx <= Get_X() + Get_Width() &&
				my >= Get_Y() && my <= Get_Y() + Get_Height()) {
				pressed = true;
			}
		}
		break;
	}
}

bool Button::is_Pressed() {
	return pressed;
}