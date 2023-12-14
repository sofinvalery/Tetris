#include "Menu.h"

enum Texture_Index {
	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_START,
	TEXTURE_INDEX_SCORES,
	TEXTURE_INDEX_INFO,
	TEXTURE_INDEX_EXIT,
	TEXTURE_INDEX_AUTHOR,
	TEXTURE_INDEX_TOTAL
};

Menu::Menu() : title_font(NULL), instructions_font(NULL), texture_array(NULL) {

}

void Menu::Init_menu() {
	title_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 80);
	instructions_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 60);
	author_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 40);

	SDL_Color white = { 255, 255, 255, 255 };

	texture_array = new Texture * [TEXTURE_INDEX_TOTAL];

	texture_array[TEXTURE_INDEX_TITLE] = new Texture;
	for (int i = 1; i < TEXTURE_INDEX_TOTAL - 1; i++) {
		texture_array[i] = new Button;
	}
	texture_array[TEXTURE_INDEX_AUTHOR] = new Texture;

	for (int i = 0; i < TEXTURE_INDEX_TOTAL; i++) {
		texture_array[i]->Set_Renderer(get_Renderer());
	}

	texture_array[TEXTURE_INDEX_TITLE]->Load_From_Renderer_Text(title_font, "Tetris", white);
	TTF_CloseFont(title_font);

	texture_array[TEXTURE_INDEX_START]->Load_From_Renderer_Text(instructions_font, "Start", white);
	texture_array[TEXTURE_INDEX_SCORES]->Load_From_Renderer_Text(instructions_font, "Scores", white);
	texture_array[TEXTURE_INDEX_INFO]->Load_From_Renderer_Text(instructions_font, "Info", white);
	texture_array[TEXTURE_INDEX_EXIT]->Load_From_Renderer_Text(instructions_font, "Exit", white);

	texture_array[TEXTURE_INDEX_AUTHOR]->Load_From_Renderer_Text(author_font, "Sofin Valeriy O725B", white);
	TTF_CloseFont(instructions_font);
}

void Menu::Draw() {
	texture_array[TEXTURE_INDEX_TITLE]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_TITLE]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_TITLE]->Get_Height()) / 2 - 250);
	texture_array[TEXTURE_INDEX_START]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_START]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_START]->Get_Height()) / 2 - 100);
	texture_array[TEXTURE_INDEX_SCORES]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_SCORES]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_SCORES]->Get_Height()) / 2 - 25);
	texture_array[TEXTURE_INDEX_INFO]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_INFO]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_INFO]->Get_Height()) / 2 + 50);
	texture_array[TEXTURE_INDEX_EXIT]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_EXIT]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_EXIT]->Get_Height()) / 2 + 125);
	texture_array[TEXTURE_INDEX_AUTHOR]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_AUTHOR]->Get_Width()) - 10,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_AUTHOR]->Get_Height()) - 10);
}

int Menu::Handle_event(SDL_Event* event) {
	switch (event->type) {
	case SDL_QUIT:
		return 0;
		break;
	case SDL_MOUSEBUTTONDOWN:
		for (int i = 1; i < TEXTURE_INDEX_TOTAL; i++) texture_array[i]->Check(event);
		if (texture_array[TEXTURE_INDEX_START]->is_Pressed()) {
			return 2;
		}
		else if (texture_array[TEXTURE_INDEX_SCORES]->is_Pressed()) {
			return 4;
		}
		else if (texture_array[TEXTURE_INDEX_INFO]->is_Pressed()) {
			return 5;
		}
		else if (texture_array[TEXTURE_INDEX_EXIT]->is_Pressed()) {
			return 0;
		}
	}
	return -1;
}