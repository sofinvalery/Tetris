#include "Window.h"

Window::Window() : mWindow(NULL), mRenderer(NULL), mFont(NULL) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Error initialization SDL " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (TTF_Init() != 0) {
        std::cout << "Error initialization TTF " << TTF_GetError() << std::endl;
        exit(1);
    }

    mWindow = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (mWindow == NULL) {
        std::cout << "Error creating window " << SDL_GetError() << std::endl;
        exit(1);
    }

    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (mRenderer == NULL) {
        std::cout << "Error creating renderer " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void Window::Clear() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
}

void Window::Render() {
    SDL_RenderPresent(mRenderer);
}

SDL_Renderer* Window::get_Renderer() {
    return mRenderer;
}

Window::~Window() {
    SDL_DestroyRenderer(mRenderer);
    mRenderer = NULL;
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;

    TTF_Quit();
    SDL_Quit();
}