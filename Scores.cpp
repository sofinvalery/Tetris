#include "Scores.h"

enum Texture_Index {
	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_NAME_TEXT,
	TEXTURE_INDEX_SCORE_TEXT,
	TEXTURE_INDEX_USER_1_NAME,
	TEXTURE_INDEX_USER_1_SCORE,
	TEXTURE_INDEX_USER_2_NAME,
	TEXTURE_INDEX_USER_2_SCORE,
	TEXTURE_INDEX_USER_3_NAME,
	TEXTURE_INDEX_USER_3_SCORE,
	TEXTURE_INDEX_USER_4_NAME,
	TEXTURE_INDEX_USER_4_SCORE,
	TEXTURE_INDEX_USER_5_NAME,
	TEXTURE_INDEX_USER_5_SCORE,
	TEXTURE_INDEX_USER_6_NAME,
	TEXTURE_INDEX_USER_6_SCORE,
	TEXTURE_INDEX_USER_7_NAME,
	TEXTURE_INDEX_USER_7_SCORE,
	TEXTURE_INDEX_USER_8_NAME,
	TEXTURE_INDEX_USER_8_SCORE,
	TEXTURE_INDEX_USER_9_NAME,
	TEXTURE_INDEX_USER_9_SCORE,
	TEXTURE_INDEX_USER_10_NAME,
	TEXTURE_INDEX_USER_10_SCORE,
	TEXTURE_INDEX_BACK_TO_MENU,
	TEXTURE_INDEX_TOTAL
};

Scores::Scores() : title_font(NULL), score_font(NULL), texture_array(NULL) {
	
}

void Scores::Init_scores() {
	title_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 80);
	score_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 40);

	SDL_Color white = { 255, 255, 255, 255 };

	texture_array = new Texture * [TEXTURE_INDEX_TOTAL];

	for (int i = 0; i < TEXTURE_INDEX_TOTAL - 1; i++)
		texture_array[i] = new Texture;

	texture_array[TEXTURE_INDEX_BACK_TO_MENU] = new Button;

	for (int i = 0; i < TEXTURE_INDEX_TOTAL; i++) {
		texture_array[i]->Set_Renderer(get_Renderer());
	}

	texture_array[TEXTURE_INDEX_TITLE]->Load_From_Renderer_Text(title_font, "Tetris", white);
	TTF_CloseFont(title_font);

	texture_array[TEXTURE_INDEX_NAME_TEXT]->Load_From_Renderer_Text(score_font, "Name", white);
	texture_array[TEXTURE_INDEX_SCORE_TEXT]->Load_From_Renderer_Text(score_font, "Score", white);

	ifstream scores_input("Scores.txt");
	while (scores_input) {
		User user;
		scores_input >> user.name >> user.score;
		Users.push_back(user);
	}
	scores_input.close();

	int k = 3;
	for (auto el : Users) {
		if (k > 21) break;
		texture_array[k++]->Load_From_Renderer_Text(score_font, el.name, white);
		texture_array[k++]->Load_From_Renderer_Text(score_font, el.score, white);
	}
	texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Load_From_Renderer_Text(score_font, "Back to menu", white);
	TTF_CloseFont(score_font);
}

void Scores::Draw() {
	texture_array[TEXTURE_INDEX_TITLE]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_TITLE]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_TITLE]->Get_Height()) / 2 - 300);

	texture_array[TEXTURE_INDEX_NAME_TEXT]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_NAME_TEXT]->Get_Width()) / 2 - 150,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_NAME_TEXT]->Get_Height()) / 2 - 225);
	texture_array[TEXTURE_INDEX_SCORE_TEXT]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_SCORE_TEXT]->Get_Width()) / 2 + 150,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_SCORE_TEXT]->Get_Height()) / 2 - 225);

	SDL_SetRenderDrawColor(get_Renderer(), 255, 255, 255, 255);
	for (int i = 0; i < 12; i++) {
		SDL_RenderDrawLine(get_Renderer(),
			SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 250 + i * 50,
			SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 250 + i * 50);
	}
	SDL_RenderDrawLine(get_Renderer(),
		SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 250 + 50 + 1,
		SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 250 + 50 + 1);
	SDL_RenderDrawLine(get_Renderer(),
		SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 250 + 50 - 1,
		SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 250 + 50 - 1);
	for (int i = 0; i < 3; i++) {
		SDL_RenderDrawLine(get_Renderer(),
			SCREEN_WIDTH / 2 - 300 + i * 300, SCREEN_HEIGHT / 2 - 250,
			SCREEN_WIDTH / 2 - 300 + i * 300, SCREEN_HEIGHT / 2 + 300);
	}

	int k = 3, i = 0;
	for (auto el : Users) {
		if (k > 21) break;
		texture_array[k]->Draw(
			(SCREEN_WIDTH - texture_array[k]->Get_Width()) / 2 - 150,
			(SCREEN_HEIGHT - texture_array[k]->Get_Height()) / 2 - 175 + 50 * i);
		texture_array[k + 1]->Draw(
			(SCREEN_WIDTH - texture_array[k + 1]->Get_Width()) / 2 + 150,
			(SCREEN_HEIGHT - texture_array[k + 1]->Get_Height()) / 2 - 175 + 50 * i);
		k += 2;
		i++;
	}
	
	texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Get_Width()) - 10,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Get_Height()) - 10);
}

int Scores::Handle_event(SDL_Event* event) {
	switch (event->type) {
	case SDL_QUIT:
		return 0;
		break;
	case SDL_MOUSEBUTTONDOWN:
		texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Check(event);

		if (texture_array[TEXTURE_INDEX_BACK_TO_MENU]->is_Pressed()) {
			return 1;
		}
	}
	return -1;
}