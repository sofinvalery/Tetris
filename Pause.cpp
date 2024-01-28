#include "Pause.h"

enum Texture_Index {
	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_PLAY,
	TEXTURE_INDEX_CHANGE_USER,
	TEXTURE_INDEX_BACK_TO_MENU,
	TEXTURE_INDEX_TOTAL
};

Pause::Pause() : title_font(NULL), information_font(NULL), texture_array(NULL) {

}

void Pause::Init_Pause() {
	title_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 60);
	information_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 40);

	SDL_Color white = { 255, 255, 255, 255 };

	texture_array = new Texture * [TEXTURE_INDEX_TOTAL];

	texture_array[TEXTURE_INDEX_TITLE] = new Texture;
	for (int i = 1; i < TEXTURE_INDEX_TOTAL; i++) {
		texture_array[i] = new Button;
	}
	for (int i = 0; i < TEXTURE_INDEX_TOTAL; i++) {
		texture_array[i]->Set_Renderer(get_Renderer());
	}

	texture_array[TEXTURE_INDEX_TITLE]->Load_From_Renderer_Text(title_font, "Tetris", white);
	TTF_CloseFont(title_font);

	texture_array[TEXTURE_INDEX_PLAY]->Load_From_Renderer_Text(information_font, "Play", white);
	texture_array[TEXTURE_INDEX_CHANGE_USER]->Load_From_Renderer_Text(information_font, "Change user", white);
	texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Load_From_Renderer_Text(information_font, "Back to menu", white);
	TTF_CloseFont(information_font);
}

void Pause::Draw() {
	texture_array[TEXTURE_INDEX_TITLE]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_TITLE]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_TITLE]->Get_Height()) / 2 - 300);
	texture_array[TEXTURE_INDEX_PLAY]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_PLAY]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_PLAY]->Get_Height()) / 2 - 150);
	texture_array[TEXTURE_INDEX_CHANGE_USER]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_CHANGE_USER]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_CHANGE_USER]->Get_Height()) / 2 - 0);
	texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Get_Height()) / 2 + 150);
}

int Pause::Handle_event(SDL_Event* event) {
	switch (event->type) {
	case SDL_QUIT:
		return 0;
		break;
	case SDL_MOUSEBUTTONDOWN:
		texture_array[TEXTURE_INDEX_PLAY]->Check(event);
		texture_array[TEXTURE_INDEX_CHANGE_USER]->Check(event);
		texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Check(event);

		if (texture_array[TEXTURE_INDEX_PLAY]->is_Pressed()) {
			return 3;
		}
		if (texture_array[TEXTURE_INDEX_CHANGE_USER]->is_Pressed()) {
			return 2;
		}
		if (texture_array[TEXTURE_INDEX_BACK_TO_MENU]->is_Pressed()) {
			return 1;
		}
	}
	return -1;
}