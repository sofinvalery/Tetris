#include "Input_User.h"

enum Texture_Index {
	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_INFORMATION,
	TEXTURE_INDEX_TEXTBOX,
	TEXTURE_INDEX_START,
	TEXTURE_INDEX_BACK_TO_MENU,
	TEXTURE_INDEX_TOTAL
};

Input_User::Input_User() : title_font(NULL), information_font(NULL), texture_array(NULL) {
	ifstream fin("Scores.txt");
	while (fin) {
		User newUser;
		fin >> newUser.name >> newUser.score;
		Users.push_back(newUser);
	}
	fin.close();
	cout << Users.size() << endl;
}

void Input_User::Init_Input_User() {
	title_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 80);
	information_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 40);

	SDL_Color white = { 255, 255, 255, 255 };

	texture_array = new Texture * [TEXTURE_INDEX_TOTAL];

	texture_array[TEXTURE_INDEX_TITLE] = new Texture;
	texture_array[TEXTURE_INDEX_INFORMATION] = new Texture;
	texture_array[TEXTURE_INDEX_TEXTBOX] = new TextBox;
	texture_array[TEXTURE_INDEX_START] = new Button;
	texture_array[TEXTURE_INDEX_BACK_TO_MENU] = new Button;

	for (int i = 0; i < TEXTURE_INDEX_TOTAL; i++) {
		texture_array[i]->Set_Renderer(get_Renderer());
	}

	texture_array[TEXTURE_INDEX_TITLE]->Load_From_Renderer_Text(title_font, "Tetris", white);

	texture_array[TEXTURE_INDEX_INFORMATION]->Load_From_Renderer_Text(information_font, "¬ведите им€ пользовател€:", white);
	texture_array[TEXTURE_INDEX_START]->Load_From_Renderer_Text(title_font, "Start", white);
	
	texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Load_From_Renderer_Text(information_font, "Back to menu", white);
	TTF_CloseFont(title_font);
	TTF_CloseFont(information_font);
}

void Input_User::Draw() {
	information_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 40);
	SDL_Color white = { 255, 255, 255, 255 };
	texture_array[TEXTURE_INDEX_TEXTBOX]->Load_From_Renderer_Text(information_font, texture_array[TEXTURE_INDEX_TEXTBOX]->Get_Input(), white);
	texture_array[TEXTURE_INDEX_TITLE]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_TITLE]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_TITLE]->Get_Height()) / 2 - 300);
	texture_array[TEXTURE_INDEX_INFORMATION]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_INFORMATION]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_INFORMATION]->Get_Height()) / 2 - 200);
	texture_array[TEXTURE_INDEX_TEXTBOX]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_TEXTBOX]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_TEXTBOX]->Get_Height()) / 2);
	texture_array[TEXTURE_INDEX_START]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_START]->Get_Width()) / 2,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_START]->Get_Height()) / 2 + 200);
	texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Draw(
		(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Get_Width()) - 10,
		(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Get_Height()) - 10);
}

int Input_User::Handle_event(SDL_Event* event) {
	SDL_StartTextInput();
	string buf;
	SDL_Color white = { 255, 255, 255, 255 };
	switch (event->type) {
	case SDL_QUIT:
		return 0;
		break;
	case SDL_MOUSEBUTTONDOWN:
		texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Check(event);
		texture_array[TEXTURE_INDEX_START]->Check(event);

		if (texture_array[TEXTURE_INDEX_BACK_TO_MENU]->is_Pressed()) {
			return 1;
		}
		else if (texture_array[TEXTURE_INDEX_START]->is_Pressed()) {
			User newUser;
			newUser.name = texture_array[TEXTURE_INDEX_TEXTBOX]->Get_Input();
			Users.push_back(newUser);
			ofstream fout("Scores.txt");
			fout.clear();
			for (auto el : Users) {
				fout << el.name << " " << el.score << "\n";
			}
			fout.close();
			return 3;
		}
	case SDL_TEXTINPUT:
		buf = texture_array[TEXTURE_INDEX_TEXTBOX]->Get_Input();
		buf += event->text.text;
		texture_array[TEXTURE_INDEX_TEXTBOX]->Set_Input(buf);
		break;
	case SDL_KEYDOWN:
		buf = texture_array[TEXTURE_INDEX_TEXTBOX]->Get_Input();
		if (event->key.keysym.sym == SDLK_BACKSPACE && buf.size()) {
			buf.pop_back();
			texture_array[TEXTURE_INDEX_TEXTBOX]->Set_Input(buf);
		}
		break;
	}
	return -1;
}