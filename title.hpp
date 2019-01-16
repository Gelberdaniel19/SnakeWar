#pragma once
#include "globals.hpp"

class TitleScreen
{
private:
	// Draws the background boxes for players to join into
	void RenderPlayerBoxes()
	{
		renderImage("assets/Player1BG.png", 33, 33);
		renderImage("assets/Player2BG.png", 416, 33);
		renderImage("assets/Player3BG.png", 33, 366);
		renderImage("assets/Player4BG.png", 416, 366);
	}

	// Draws the appropriate message into each player box
	void RenderPlayerMessages()
	{
		for (int i = 0; i < 4; i++) {
			std::string text2 = "Player " + std::to_string(i+1);

			// Load the text texture based on if the player is ready
			TextTexture t;
			if (playerCount() < i+1) t = makeTextWithShadow("Press \'A\'", 30, COLOR_BG, 1, COLOR_BLACK);
			else t = makeTextWithShadow(text2, 45, COLOR_WHITE, 3, COLOR_BLACK);

			// Render the text based on which player it is
			if (i == 0) renderText(t, 33+350/2-t.w/2, 33+300/2-t.h/2);
			if (i == 1) renderText(t, 416+350/2-t.w/2, 33+300/2-t.h/2);
			if (i == 2) renderText(t, 33+350/2-t.w/2, 366+300/2-t.h/2);
			if (i == 3) renderText(t, 416+350/2-t.w/2, 366+300/2-t.h/2);
		}
	}

	// Draws the message to begin the game, only if there is a player
	void RenderStartMessage()
	{
		if (playerCount() >= 1) {
			TextTexture t = makeTextWithShadow("Press \'start\' to play", 55, 230, 230, 255, 3, 30, 30, 30);
			renderText(t, WIN_WIDTH/2-t.w/2, 700);
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
		// First render
		ClearData();
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
						if (!getPlayerNum(cnum))
							addPlayer(cnum);

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
