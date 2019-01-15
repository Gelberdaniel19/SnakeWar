#pragma once
#include "globals.hpp"

class TitleScreen
{
private:
	// Draws the background boxes for players to join into
	void RenderPlayerBoxes()
	{
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
	}

	// Draws the appropriate message into each player box
	void RenderPlayerMessages()
	{
		// Preload fonts
		TTF_Font* font1 = TTF_OpenFont("assets/upheavtt.ttf", 30);
		SDL_Color color1 = {COLOR_BG};
		std::string message1 = "Press \'A\'";
		TTF_Font* font2 = TTF_OpenFont("assets/upheavtt.ttf", 45);
		SDL_Color color2 = {0, 0, 0};

		// Draw messages
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

		// Cleanup
		TTF_CloseFont(font1);
		TTF_CloseFont(font2);
	}

	// Draws the message to begin the game, only if there is a player
	void RenderStartMessage()
	{
		if (playerCount() >= 1) {
			TTF_Font* font = TTF_OpenFont("assets/upheavtt.ttf", 55);
			SDL_Color color = {230, 230, 255};

			SDL_Surface* temp = TTF_RenderText_Solid(font, "Press \'start\' to play", color);
			SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, temp);
			SDL_Rect rect{WIN_WIDTH/2-temp->w/2, 700, temp->w, temp->h};

			SDL_RenderCopy(renderer, message, NULL, &rect);
			SDL_FreeSurface(temp);
			SDL_DestroyTexture(message);

			TTF_CloseFont(font);
		}
	}

	// The main render method for the title screen.
	// Only called when an update is made
	void RenderTitleScreen()
	{
		SDL_RenderClear(renderer);

		RenderPlayerBoxes();
		RenderPlayerMessages();
		RenderStartMessage();

		SDL_RenderPresent(renderer);
	}

	// Clears player data. This is for when players finish the game
	// and return to the title screen.
	void ClearData()
	{
		// Load controllers
	    for (int i = 0; i < SDL_NumJoysticks() && i < 8; i++)
			if (SDL_IsGameController(i))
				controllers.at(i) = SDL_GameControllerOpen(i);

		// Reset bindings
		for (int i = 0; i < 4; i++)
			bindings[i] = -1;
	}

public:
	// The main loop for the title screen
	void Start()
	{
		ClearData();

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
					if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
						if (!getPlayerNum(cnum)) {
							addPlayer(cnum);
						}
					}
					// Starts the game
					if (e.cbutton.button == SDL_CONTROLLER_BUTTON_START)
						if (getPlayerNum(cnum))
							selecting = false;
					RenderTitleScreen();
					break;
				}
			}
		}
	}
};
