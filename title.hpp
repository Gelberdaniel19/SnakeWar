#pragma once
#include "globals.hpp"

struct TitleScreen
{

void RenderTitleScreen()
{
	int playercount = playerCount();
	SDL_RenderClear(renderer);

	// Player menu boxes
	for (int i = 0; i < 4; i++) {
		std::string path = "assets/Player" + std::to_string(i+1) + "BG.png";
		SDL_Surface* surface = IMG_Load(path.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_Rect rect;
		if (i == 0) rect = {33, 33, 350, 350};
		if (i == 1) rect = {416, 33, 350, 350};
		if (i == 2) rect = {33, 416, 350, 350};
		if (i == 3) rect = {416, 416, 350, 350};
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}

	// Player join messages
	TTF_Font* font = TTF_OpenFont("assets/FreeMono.ttf", 20);
	SDL_Color black = {0, 0, 0};
	std::string message1 = "Press \"A\" to join";
	std::string message2 = "Press \"start\" to play";

	for (int i = 0; i < 4; i++) {
		SDL_Surface* temp = TTF_RenderText_Solid(font, playerCount() < i+1 ? message1.c_str() : message2.c_str(), black);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, temp);
		SDL_Rect rect{0, 0, temp->w, temp->h};
		if (i == 0) rect = {33+350/2-temp->w/2, 33+350/2-temp->h/2, temp->w, temp->h};
		else if (i == 1) rect = {416+350/2-temp->w/2, 33+350/2-temp->h/2, temp->w, temp->h};
		else if (i == 2) rect = {33+350/2-temp->w/2, 416+350/2-temp->h/2, temp->w, temp->h};
		else rect = {416+350/2-temp->w/2, 416+300/2-temp->h/2, temp->w, temp->h};

		SDL_RenderCopy(renderer, message, NULL, &rect);
		SDL_FreeSurface(temp);
		SDL_DestroyTexture(message);
	}

	SDL_RenderPresent(renderer);
}

void Start()
{
	// First render
	RenderTitleScreen();

	// User select loop
	SDL_Event e;
	bool selecting = true;
	while (selecting && running) {
		// Input
		while(SDL_PollEvent(&e)){
			switch(e.type){
			case SDL_QUIT:
				running = false;
				break;

			case SDL_CONTROLLERBUTTONDOWN:
				int cnum = e.cbutton.which;
				// Binds players to controllers
				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A)
					if (!playerExists(cnum))
						addPlayer(cnum);
				// Starts the game
				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_START)
					if (playerExists(cnum))
						selecting = false;
				RenderTitleScreen();
				break;
			}
		}
	}
}

};
