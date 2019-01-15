#pragma once
#include "globals.hpp"

class GameOver
{
private:
    int winner = -1;

    // Renders the Game Over screen
    void RenderGameOver() {}

public:
    // Main loop of the Game Over screen.
    // Returns OPTION_AGAIN or OPTION_MENU
    int Start(int winner)
    {
        // Initial game over screen
        this->winner = winner;
        RenderGameOver();

        // Menu loop
        SDL_Event e;
		bool selecting = true;
		while (selecting && running) {
			// Input
			while(SDL_PollEvent(&e)){
				switch(e.type){
				case SDL_QUIT:
					running = false;
                    return OPTION_MENU;
					break;

				case SDL_CONTROLLERBUTTONDOWN:
					int cnum = e.cbutton.which;
					// Binds players to controllers
					if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A)
						if (playerExists(cnum))
							return OPTION_AGAIN;
					// Starts the game
					if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B)
						if (playerExists(cnum))
							return OPTION_MENU;
					break;
				}
			}
		}
    }
};
