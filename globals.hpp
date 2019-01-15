#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <string>

// Colors
#define COLOR_BG 44,62,80
#define COLOR_P1 231,76,48
#define COLOR_P2 46,204,112
#define COLOR_P3 155,89,176
#define COLOR_P4 241,196,0
#define COLOR_WALL 170,170,200
#define COLOR_FOOD 255,220,220

// Game over options
#define OPTION_AGAIN 0
#define OPTION_MENU 1

// Directions
#define DIR_NONE 0
#define DIR_UP 1
#define DIR_DOWN 2
#define DIR_LEFT 3
#define DIR_RIGHT 4

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = WIN_WIDTH;
const int STARTING_TAIL = 5;
const int TAIL_GAIN = 5;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool running = true;

// Text creation
struct TextTexture {
	int w, h;
	SDL_Texture* texture;
};
TextTexture makeText(std::string text, int fontSize, Uint8 r, Uint8 g, Uint8 b) {
	TTF_Font* font = TTF_OpenFont("assets/upheavtt.ttf", fontSize);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color{r, g, b});
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	TextTexture result{surface->w, surface->h, tex};
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return result;
}
void renderText(TextTexture t, int x, int y) {
	SDL_Rect rect{x, y, t.w, t.h};
	SDL_RenderCopy(renderer, t.texture, NULL, &rect);
	SDL_DestroyTexture(t.texture);
}

// Image creation
void renderImage(std::string path, int x, int y) {
	SDL_Surface* surface = IMG_Load(path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect rect{x, y, surface->w, surface->h};
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

// Player management
std::vector<SDL_GameController*> controllers(8, nullptr);
int bindings[4] = {-1, -1, -1, -1};

int playerCount() {
	for (int i = 0; i < 4; i++)
		if (bindings[i] == -1) return i;
}
void addPlayer(int cnum) {
	for (int i = 0; i < 4; i++) {
		if (bindings[i] == -1) {
			bindings[i] = cnum;
			break;
		}
	}
}
int getPlayerNum(int cnum) {
	for (int i = 0; i < 4; i++) {
		if (bindings[i] == cnum) return i+1;
	}
	return 0;
}
