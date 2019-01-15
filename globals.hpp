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
int binding1 = -1;
int binding2 = -1;
int binding3 = -1;
int binding4 = -1;

int playerCount()
{
	if (binding1 == -1) return 0;
	else if (binding2 == -1) return 1;
	else if (binding3 == -1) return 2;
	else if (binding4 == -1) return 3;
	else return 4;
}
void addPlayer(int cnum)
{
	if (binding1 == -1)
		binding1 = cnum;
	else if (binding2 == -1)
		binding2 = cnum;
	else if (binding3 == -1)
		binding3 = cnum;
	else if (binding4 == -1)
		binding4 = cnum;
}
bool playerExists(int cnum)
{
	return (binding1 == cnum ||
			binding2 == cnum ||
			binding3 == cnum ||
			binding4 == cnum);
}
int getPlayerNum(int cnum)
{
	if (binding1 == cnum) return 1;
	else if (binding2 == cnum) return 2;
	else if (binding3 == cnum) return 3;
	else if (binding4 == cnum) return 4;
	else return 0;
}
