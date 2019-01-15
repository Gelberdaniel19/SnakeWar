#pragma once
#include "globals.hpp"

class TitleScreen
{
private:
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
		if (i == 0) rect = {33, 33, 350, 300};
		if (i == 1) rect = {416, 33, 350, 300};
		if (i == 2) rect = {33, 366, 350, 300};
		if (i == 3) rect = {416, 366, 350, 300};
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}

	// Player join messages
	TTF_Font* font1 = TTF_OpenFont("assets/upheavtt.ttf", 30);
	SDL_Color color1 = {COLOR_BG};
	std::string message1 = "Press \'A\'";
	TTF_Font* font2 = TTF_OpenFont("assets/upheavtt.ttf", 45);
	SDL_Color color2 = {0, 0, 0};
	TTF_Font* font3 = TTF_OpenFont("assets/upheavtt.ttf", 55);
	SDL_Color color3 = {230, 230, 255};

	for (int i = 0; i < 4; i++) {
		std::string message2 = "Player " + std::to_string(i+1);
		SDL_Surface* temp;

		// Render the message for either prompting the user to join
		// or telling them their player number
		if (playerCount() < i+1)
			temp = TTF_RenderText_Solid(font1, message1.c_str(), color1);
		else
		  	temp = TTF_RenderText_Solid(font2, message2.c_str(), color2);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, temp);
		SDL_Rect rect{0, 0, temp->w, temp->h};
		if (i == 0) rect = {33+350/2-temp->w/2, 33+300/2-temp->h/2, temp->w, temp->h};
		else if (i == 1) rect = {416+350/2-temp->w/2, 33+300/2-temp->h/2, temp->w, temp->h};
		else if (i == 2) rect = {33+350/2-temp->w/2, 366+300/2-temp->h/2, temp->w, temp->h};
		else rect = {416+350/2-temp->w/2, 366+300/2-temp->h/2, temp->w, temp->h};

		SDL_RenderCopy(renderer, message, NULL, &rect);
		SDL_FreeSurface(temp);
		SDL_DestroyTexture(message);
	}

	// Start message
	if (playerCount() >= 1) {
		SDL_Surface* temp = TTF_RenderText_Solid(font3, "Press \'start\' to play", color3);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, temp);
		SDL_Rect rect{WIN_WIDTH/2-temp->w/2, 700, temp->w, temp->h};

		SDL_RenderCopy(renderer, message, NULL, &rect);
		SDL_FreeSurface(temp);
		SDL_DestroyTexture(message);
	}

	// Clean up
	TTF_CloseFont(font1);
	TTF_CloseFont(font2);
	TTF_CloseFont(font3);

	SDL_RenderPresent(renderer);
}

public:
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
