#include "Scene.h"

Scene::Scene() : mRenderer(NULL) {}

void Scene::set_Renderer(SDL_Renderer* renderer) {
	mRenderer = renderer;
}

SDL_Renderer* Scene::get_Renderer() {
	return mRenderer;
}

void Scene::Clear() {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
}

void Scene::Render() {
	SDL_RenderPresent(mRenderer);
}