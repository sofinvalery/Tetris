#include "Info.h"

enum Texture_Index {
	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_INFORMATION,
	TEXTURE_INDEX_INFO_RU_0,
	TEXTURE_INDEX_INFO_RU_1,
	TEXTURE_INDEX_INFO_RU_2,
	TEXTURE_INDEX_INFO_RU_3,
	TEXTURE_INDEX_INFO_RU_4,
	TEXTURE_INDEX_INFO_RU_5,
	TEXTURE_INDEX_INFO_RU_6,
	TEXTURE_INDEX_INFO_RU_7,
	TEXTURE_INDEX_BACK_TO_MENU,
	TEXTURE_INDEX_TOTAL
};

Info::Info() : title_font(NULL), information_font(NULL), texture_array(NULL) {

}

void Info::Init_info() {
	title_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 80);
	information_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 40);
	info_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 20);

	SDL_Color white = { 255, 255, 255, 255 };

	texture_array = new Texture * [TEXTURE_INDEX_TOTAL];

	texture_array[TEXTURE_INDEX_TITLE] = new Texture;
	texture_array[TEXTURE_INDEX_INFORMATION] = new Texture;
	texture_array[TEXTURE_INDEX_INFO_RU_0] = new Texture;
	texture_array[TEXTURE_INDEX_INFO_RU_1] = new Texture;
	texture_array[TEXTURE_INDEX_INFO_RU_2] = new Texture;
	texture_array[TEXTURE_INDEX_INFO_RU_3] = new Texture;
	texture_array[TEXTURE_INDEX_INFO_RU_4] = new Texture;
	texture_array[TEXTURE_INDEX_INFO_RU_5] = new Texture;
	texture_array[TEXTURE_INDEX_INFO_RU_6] = new Texture;
	texture_array[TEXTURE_INDEX_INFO_RU_7] = new Texture;
	texture_array[TEXTURE_INDEX_BACK_TO_MENU] = new Button;

	for (int i = 0; i < TEXTURE_INDEX_TOTAL; i++) {
		texture_array[i]->Set_Renderer(get_Renderer());
	}

	texture_array[TEXTURE_INDEX_TITLE]->Load_From_Renderer_Text(title_font, "Tetris", white);
	TTF_CloseFont(title_font);

	string info_string_ru_0 = "ѕравила игры: ";
	string info_string_ru_1 = "1. —лучайные фигурки падают сверху";
	string info_string_ru_2 = "2. ¬ полете можно повернуть фигурку (нажать стрелку вверх)";
	string info_string_ru_3 = "3. ћожно ускорить скорость падени€ (нажать стрелку вниз)";
	string info_string_ru_4 = "4. ‘игурка падает пока не столкнетс€ с другой фигуркой или с дном";
	string info_string_ru_5 = "5. ≈сли горизонтальный р€д полностью заполнилс€, то он исчезает и все остальное опускаетс€ вниз";
	string info_string_ru_6 = "6. ¬ы проиграли, когда не можете поместить новую фигурку";
	string info_string_ru_7 = "7. «а каждый заполненный р€д игрок получает 100 очков";

	texture_array[TEXTURE_INDEX_INFORMATION]->Load_From_Renderer_Text(information_font, "ѕравила игры:", white);
	texture_array[TEXTURE_INDEX_INFO_RU_1]->Load_From_Renderer_Text(info_font, info_string_ru_1, white);
	texture_array[TEXTURE_INDEX_INFO_RU_2]->Load_From_Renderer_Text(info_font, info_string_ru_2, white);
	texture_array[TEXTURE_INDEX_INFO_RU_3]->Load_From_Renderer_Text(info_font, info_string_ru_3, white);
	texture_array[TEXTURE_INDEX_INFO_RU_4]->Load_From_Renderer_Text(info_font, info_string_ru_4, white);
	texture_array[TEXTURE_INDEX_INFO_RU_5]->Load_From_Renderer_Text(info_font, info_string_ru_5, white);
	texture_array[TEXTURE_INDEX_INFO_RU_6]->Load_From_Renderer_Text(info_font, info_string_ru_6, white);
	texture_array[TEXTURE_INDEX_INFO_RU_7]->Load_From_Renderer_Text(info_font, info_string_ru_7, white);
	texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Load_From_Renderer_Text(information_font, "Back to menu", white);
	TTF_CloseFont(information_font);
}

void Info::Draw() {
	texture_array[TEXTURE_INDEX_TITLE]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_TITLE]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_TITLE]->Get_Height()) / 2 - 300);
	texture_array[TEXTURE_INDEX_INFORMATION]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_INFORMATION]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_INFORMATION]->Get_Height()) / 2 - 200);
	texture_array[TEXTURE_INDEX_INFO_RU_1]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_INFO_RU_1]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_INFO_RU_1]->Get_Height()) / 2 - 100);
	texture_array[TEXTURE_INDEX_INFO_RU_2]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_INFO_RU_2]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_INFO_RU_2]->Get_Height()) / 2 - 50);
	texture_array[TEXTURE_INDEX_INFO_RU_3]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_INFO_RU_3]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_INFO_RU_3]->Get_Height()) / 2 - 0);
	texture_array[TEXTURE_INDEX_INFO_RU_4]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_INFO_RU_4]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_INFO_RU_4]->Get_Height()) / 2 + 50);
	texture_array[TEXTURE_INDEX_INFO_RU_5]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_INFO_RU_5]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_INFO_RU_5]->Get_Height()) / 2 + 100);
	texture_array[TEXTURE_INDEX_INFO_RU_6]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_INFO_RU_6]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_INFO_RU_6]->Get_Height()) / 2 + 150);
	texture_array[TEXTURE_INDEX_INFO_RU_7]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_INFO_RU_7]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_INFO_RU_7]->Get_Height()) / 2 + 200);
	texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Get_Width()) - 10,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Get_Height()) - 10);
}

int Info::Handle_event(SDL_Event* event) {
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