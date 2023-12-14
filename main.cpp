#include "Window.h"
#include "Texture.h"
#include "Scene.h"
#include "Menu.h"
#include "Scores.h"
#include "Info.h"
#include "Input_User.h"
#include "Game.h"

int main(int argc, char* argv[]) {
	Window* win = new Window;
	bool quit = false;

	Scene* scene = new Menu;
	scene->set_Renderer(win->get_Renderer());
	scene->Init_menu();

	SDL_Event event;

	while (!quit) {
		SDL_PollEvent(&event);
		switch (scene->Handle_event(&event)) {
		case 0:
			quit = true;
			break;
		case 1:
			delete scene;
			scene = new Menu;
			scene->set_Renderer(win->get_Renderer());
			scene->Init_menu();
			SDL_FlushEvent(SDLK_0);
			break;
		case 2:
			delete scene;
			scene = new Input_User;
			scene->set_Renderer(win->get_Renderer());
			scene->Init_Input_User();
			SDL_FlushEvent(SDLK_0);
			break;
		case 3:
			delete scene;
			scene = new Game;
			scene->set_Renderer(win->get_Renderer());
			scene->Init_game();
			SDL_FlushEvent(SDLK_0);
			break;
		case 4:
			delete scene;
			scene = new Scores;
			scene->set_Renderer(win->get_Renderer());
			scene->Init_scores();
			SDL_FlushEvent(SDLK_0);
			break;
		case 5:
			delete scene;
			scene = new Info;
			scene->set_Renderer(win->get_Renderer());
			scene->Init_info();
			SDL_FlushEvent(SDLK_0);
			break;
		}
		scene->Clear();
		scene->Draw();
		scene->Render();
	}
	return 0;
}