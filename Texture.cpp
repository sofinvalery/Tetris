#include "Texture.h"

Texture::Texture() : mTexture(NULL), mRenderer(NULL), mX(0), mY(0), mWidth(0), mHeight(0) {}

Texture::~Texture() {
	Free();
}

void Texture::Set_Renderer(SDL_Renderer* renderer) {
	mRenderer = renderer;
}

bool Texture::Load_From_Renderer_Text(TTF_Font* font, string texture_text, SDL_Color text_color) {
	Free();
	texture_text = texture_text.size() ? texture_text : " ";
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, texture_text.c_str(), text_color);
	if (text_surface == NULL) {
		cout << "Error render text surface : " << TTF_GetError() << endl;
		return false;
	}

	mTexture = SDL_CreateTextureFromSurface(mRenderer, text_surface);
	if (mTexture == NULL) {
		cout << "Error create texture from surface : " << SDL_GetError() << endl;
		return false;
	}

	mWidth = text_surface->w ? text_surface->w : 1;
	mHeight = text_surface->h ? text_surface->h : 1;

	SDL_FreeSurface(text_surface);

	return true;
}

void Texture::Free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::Set_Color(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::Set_Alpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::Draw(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	mX = x;
	mY = y;

	SDL_Rect render_quad = { mX, mY, mWidth, mHeight };

	if (clip != NULL) {
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}

	SDL_RenderCopyEx(mRenderer, mTexture, clip, &render_quad, angle, center, flip);
}

int Texture::Get_X() { return mX; }
int Texture::Get_Y() { return mY; }
int Texture::Get_Width() { return mWidth; }
int Texture::Get_Height() { return mHeight; }