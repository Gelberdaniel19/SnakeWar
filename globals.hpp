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

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool running = true;

// Player management
std::vector<SDL_GameController*> controllers(8, nullptr);
int controller1 = -1;
int controller2 = -1;
int controller3 = -1;
int controller4 = -1;

int playerCount()
{
	if (controller1 == -1) return 0;
	else if (controller2 == -1) return 1;
	else if (controller3 == -1) return 2;
	else if (controller4 == -1) return 3;
	else return 4;
}
void addPlayer(int cnum)
{
	if (controller1 == -1)
		controller1 = cnum;
	else if (controller2 == -1)
		controller2 = cnum;
	else if (controller3 == -1)
		controller3 = cnum;
	else if (controller4 == -1)
		controller4 = cnum;
}
bool playerExists(int cnum)
{
	return (controller1 == cnum ||
			controller2 == cnum ||
			controller3 == cnum ||
			controller4 == cnum);
}
int getPlayerNum(int cnum)
{
	if (controller1 == cnum) return 1;
	else if (controller2 == cnum) return 2;
	else if (controller3 == cnum) return 3;
	else if (controller4 == cnum) return 4;
	else return 0;
}
