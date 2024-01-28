#include "Game.h"

enum Texture_Index {
	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_UP_ARROW,
	TEXTURE_INDEX_RIGHT_ARROW,
	TEXTURE_INDEX_LEFT_ARROW,
	TEXTURE_INDEX_DOWN_ARROW,
	TEXTURE_INDEX_SCORE,
	TEXTURE_INDEX_USER_SCORE,
	TEXTURE_INDEX_NEXT,
	TEXTURE_INDEX_PAUSE,
	TEXTURE_INDEX_GAME_OVER,
	TEXTURE_INDEX_SCORES,
	TEXTURE_INDEX_BACK_TO_MENU,
	TEXTURE_INDEX_EXIT,
	TEXTURE_INDEX_TOTAL
};

Game::Game() : title_font(NULL), info_font(NULL), texture_array(NULL), current_board(NULL) {
	ifstream fin("Scores.txt");
	while (fin) {
		User newUser;
		fin >> newUser.name >> newUser.score;
		Users.push_back(newUser);
	}
	fin.close();
}

void Game::Init_game() {
	current_board = new Board;

	current_board->Set_Renderer(get_Renderer());

	title_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 80);
	info_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 40);
	information_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 16);

	SDL_Color red = { 255, 25, 25, 200 };
	SDL_Color white = { 255, 255, 255, 255 };

	texture_array = new Texture * [TEXTURE_INDEX_TOTAL];

	texture_array[TEXTURE_INDEX_TITLE] = new Texture;
	texture_array[TEXTURE_INDEX_UP_ARROW] = new Texture;
	texture_array[TEXTURE_INDEX_RIGHT_ARROW] = new Texture;
	texture_array[TEXTURE_INDEX_LEFT_ARROW] = new Texture;
	texture_array[TEXTURE_INDEX_DOWN_ARROW] = new Texture;
	texture_array[TEXTURE_INDEX_SCORE] = new Texture;
	texture_array[TEXTURE_INDEX_USER_SCORE] = new TextBox;
	texture_array[TEXTURE_INDEX_NEXT] = new Texture;
	texture_array[TEXTURE_INDEX_PAUSE] = new Button;

	texture_array[TEXTURE_INDEX_GAME_OVER] = new Texture;
	texture_array[TEXTURE_INDEX_SCORES] = new Button;
	texture_array[TEXTURE_INDEX_BACK_TO_MENU] = new Button;
	texture_array[TEXTURE_INDEX_EXIT] = new Button;

	for (int i = 0; i < TEXTURE_INDEX_TOTAL; i++) {
		texture_array[i]->Set_Renderer(get_Renderer());
	}

	texture_array[TEXTURE_INDEX_TITLE]->Load_From_Renderer_Text(title_font, "Tetris", white);
	texture_array[TEXTURE_INDEX_GAME_OVER]->Load_From_Renderer_Text(title_font, "Game over", white);
	TTF_CloseFont(title_font);

	string info_up_arrow = "Стрелка вверх - переворот фигуры";
	string info_right_arrow = "Стрелка вправо - движение фигуры вправо";
	string info_left_arrow = "Стрелка влево - движение фигуры влево";
	string info_down_arrow = "Стрелка вниз - ускорение падения";

	texture_array[TEXTURE_INDEX_UP_ARROW]->Load_From_Renderer_Text(information_font, info_up_arrow, white);
	texture_array[TEXTURE_INDEX_RIGHT_ARROW]->Load_From_Renderer_Text(information_font, info_right_arrow, white);
	texture_array[TEXTURE_INDEX_LEFT_ARROW]->Load_From_Renderer_Text(information_font, info_left_arrow, white);
	texture_array[TEXTURE_INDEX_DOWN_ARROW]->Load_From_Renderer_Text(information_font, info_down_arrow, white);
	TTF_CloseFont(information_font);

	user_score = atoi(Users[Users.size()-1].name.c_str());

	texture_array[TEXTURE_INDEX_SCORE]->Load_From_Renderer_Text(info_font, "Score", white);
	texture_array[TEXTURE_INDEX_USER_SCORE]->Load_From_Renderer_Text(info_font, to_string(user_score), white);
	texture_array[TEXTURE_INDEX_NEXT]->Load_From_Renderer_Text(info_font, "Next", white);
	texture_array[TEXTURE_INDEX_PAUSE]->Load_From_Renderer_Text(info_font, "Pause", white);

	texture_array[TEXTURE_INDEX_SCORES]->Load_From_Renderer_Text(info_font, "Scores", white);
	texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Load_From_Renderer_Text(info_font, "Back to menu", white);
	texture_array[TEXTURE_INDEX_EXIT]->Load_From_Renderer_Text(info_font, "Exit", white);
	TTF_CloseFont(info_font);
}

void Game::Draw() {
	if (!flag) {
		texture_array[TEXTURE_INDEX_USER_SCORE]->Set_Input(to_string(user_score));
		information_font = TTF_OpenFont("DS Pixel Cyr Regular.ttf", 40);
		SDL_Color white = { 255, 255, 255, 255 };
		texture_array[TEXTURE_INDEX_USER_SCORE]->Load_From_Renderer_Text(information_font, texture_array[TEXTURE_INDEX_USER_SCORE]->Get_Input(), white);

		texture_array[TEXTURE_INDEX_TITLE]->Draw(
			(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_TITLE]->Get_Width()) / 4 - 150,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_TITLE]->Get_Height()) / 4 - 150);
		texture_array[TEXTURE_INDEX_UP_ARROW]->Draw(
			(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_UP_ARROW]->Get_Width()) / 4 - 175,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_UP_ARROW]->Get_Height()) / 2 - 75);
		texture_array[TEXTURE_INDEX_RIGHT_ARROW]->Draw(
			(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_RIGHT_ARROW]->Get_Width()) / 4 - 175,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_RIGHT_ARROW]->Get_Height()) / 2 - 25);
		texture_array[TEXTURE_INDEX_LEFT_ARROW]->Draw(
			(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_LEFT_ARROW]->Get_Width()) / 4 - 175,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_LEFT_ARROW]->Get_Height()) / 2 + 25);
		texture_array[TEXTURE_INDEX_DOWN_ARROW]->Draw(
			(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_DOWN_ARROW]->Get_Width()) / 4 - 175,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_DOWN_ARROW]->Get_Height()) / 2 + 75);
		current_board->Draw_Board();
		if (current_board->Tick() == 0) {
			flag = true;
		}
		user_score = current_board->Get_Score();
		texture_array[TEXTURE_INDEX_SCORE]->Draw(
			3 * (SCREEN_WIDTH - texture_array[TEXTURE_INDEX_SCORE]->Get_Width()) / 4 + 175,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_SCORE]->Get_Height()) / 4 - 50);
		texture_array[TEXTURE_INDEX_USER_SCORE]->Draw(
			3 * (SCREEN_WIDTH - texture_array[TEXTURE_INDEX_USER_SCORE]->Get_Width()) / 4 + 175,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_USER_SCORE]->Get_Height()) / 4 - 0);
		texture_array[TEXTURE_INDEX_NEXT]->Draw(
			3 * (SCREEN_WIDTH - texture_array[TEXTURE_INDEX_NEXT]->Get_Width()) / 4 + 175,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_NEXT]->Get_Height()) / 4 + 100);
		texture_array[TEXTURE_INDEX_PAUSE]->Draw(
			(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_PAUSE]->Get_Width()) - 10,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_PAUSE]->Get_Height()) - 10);
	}
	else {
		texture_array[TEXTURE_INDEX_GAME_OVER]->Draw(
			(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_GAME_OVER]->Get_Width()) / 2,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_GAME_OVER]->Get_Height()) / 2 - 200);
		texture_array[TEXTURE_INDEX_SCORES]->Draw(
			(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_SCORES]->Get_Width()) / 2,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_SCORES]->Get_Height()) / 2 - 75);
		texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Draw(
			(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Get_Width()) / 2,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Get_Height()) / 2 + 0);
		texture_array[TEXTURE_INDEX_EXIT]->Draw(
			(SCREEN_WIDTH - texture_array[TEXTURE_INDEX_EXIT]->Get_Width()) / 2,
			(SCREEN_HEIGHT - texture_array[TEXTURE_INDEX_EXIT]->Get_Height()) / 2 + 75);
	}
	SDL_Delay(50);
}

int Game::Handle_event(SDL_Event* event) {
	ofstream fout("Scores.txt");
	switch (event->type) {
	case SDL_QUIT:
		Users[Users.size() - 1].score = to_string(user_score);
		sort(Users.begin(), Users.end());
		fout.clear();
		for (int i = 0; i < 10 && i < Users.size(); i++) {
			fout << Users[i].name << " " << Users[i].score << "\n";
		}
		fout.close();
		return 0;
		break;
	case SDL_MOUSEBUTTONDOWN:
		texture_array[TEXTURE_INDEX_PAUSE]->Check(event);

		texture_array[TEXTURE_INDEX_SCORES]->Check(event);
		texture_array[TEXTURE_INDEX_BACK_TO_MENU]->Check(event);
		texture_array[TEXTURE_INDEX_EXIT]->Check(event);

		if (texture_array[TEXTURE_INDEX_PAUSE]->is_Pressed()) {
			Pause* game_pause = new Pause;
			game_pause->set_Renderer(get_Renderer());
			game_pause->Init_Pause();
			bool is_pause = true;
			while (is_pause) {
				SDL_PollEvent(event);
				switch (game_pause->Handle_event(event)) {
				case 0:
					Users[Users.size() - 1].score = to_string(user_score);
					sort(Users.begin(), Users.end());
					fout.clear();
					for (int i = 0; i < 10 && i < Users.size(); i++) {
						fout << Users[i].name << " " << Users[i].score << "\n";
					}
					fout.close();
					return 0;
					break;
				case 1:
					Users[Users.size() - 1].score = to_string(user_score);
					sort(Users.begin(), Users.end());
					fout.clear();
					for (int i = 0; i < 10 && i < Users.size(); i++) {
						fout << Users[i].name << " " << Users[i].score << "\n";
					}
					fout.close();
					//cout << "Back to menu" << endl;
					return 1;
					break;
				case 2:
					Users[Users.size() - 1].score = to_string(user_score);
					sort(Users.begin(), Users.end());
					fout.clear();
					for (int i = 0; i < 10 && i < Users.size(); i++) {
						fout << Users[i].name << " " << Users[i].score << "\n";
					}
					fout.close();
					//cout << "Change user" << endl;
					return 2;
					break;
				case 3:
					//cout << "Play" << endl;
					is_pause = false;
					break;
				}
				game_pause->Clear();
				game_pause->Draw();
				game_pause->Render();
			}
		}
		if (texture_array[TEXTURE_INDEX_SCORES]->is_Pressed()) {
			Users[Users.size() - 1].score = to_string(user_score);
			sort(Users.begin(), Users.end());
			fout.clear();
			for (int i = 0; i < 10 && i < Users.size(); i++) {
				fout << Users[i].name << " " << Users[i].score << "\n";
			}
			fout.close();
			return 4;
		}
		if (texture_array[TEXTURE_INDEX_EXIT]->is_Pressed()) {
			Users[Users.size() - 1].score = to_string(user_score);
			sort(Users.begin(), Users.end());
			fout.clear();
			for (int i = 0; i < 10 && i < Users.size(); i++) {
				fout << Users[i].name << " " << Users[i].score << "\n";
			}
			fout.close();
			return 0;
		}
		if (texture_array[TEXTURE_INDEX_BACK_TO_MENU]->is_Pressed()) {
			Users[Users.size() - 1].score = to_string(user_score);
			sort(Users.begin(), Users.end());
			fout.clear();
			for (int i = 0; i < 10 && i < Users.size(); i++) {
				fout << Users[i].name << " " << Users[i].score << "\n";
			}
			fout.close();
			return 1;
		}
	case SDL_KEYDOWN:
		current_board->Handle_event(event);
		break;
	}
	return -1;
}