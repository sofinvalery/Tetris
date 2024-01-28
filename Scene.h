#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "Globals.h"

class Scene {
private:
	SDL_Renderer* mRenderer;

public:
	Scene();

	void set_Renderer(SDL_Renderer* renderer);
	SDL_Renderer* get_Renderer();

	struct User {
		std::string name;
		std::string score;
	};
	std::vector <User> Users;

	void set_Vector(std::vector<User> Users) { this->Users = Users; }
	std::vector<User> get_Vector() { return this->Users; }

	friend bool operator < (User first, User second) {
		return atoi(first.score.c_str()) > atoi(second.score.c_str());
	}

	void Clear();

	void Render();

	virtual void Init_menu() {}
	virtual void Init_scores() {}
	virtual void Init_info() {}
	virtual void Init_Input_User() {}
	virtual void Init_game() {}
	virtual void Init_Pause() {}
	virtual void Init_Game_Over() {}
	virtual void Draw() {}
	virtual int Handle_event(SDL_Event* event) { return -1; }

};