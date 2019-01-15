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
const int CONTROLLER_DEADZONE = 10000;
const int STARTING_TAIL = 5;
const int TAIL_GAIN = 5;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool running = true;

// Player management
std::vector<SDL_GameController*> controllers(8, nullptr);
std::vector<int> bindings(4, -1);

int playerCount()
{
	for (int i = 0; i < 4; i++)
		if (bindings[i] == -1) return i;
}

void addPlayer(int cnum)
{
	for (int i = 0; i < 4; i++) {
		if (bindings[i] == -1) {
			bindings[i] = cnum;
			break;
		}
	}
}

int getPlayerNum(int cnum)
{
	for (int i = 0; i < 4; i++) {
		if (bindings[i] == cnum) return i+1;
	}
	return 0;
}
