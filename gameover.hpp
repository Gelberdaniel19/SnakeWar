#pragma once
#include "globals.hpp"

class GameOver
{
private:
    int winner = -1;

    // Renders a box of the color of the player who won
    // which says "Player x wins!"
    void RenderVictoryBox()
    {
        // No victory box for practice mode
        if (winner == -1) return;

        // Box for winner
        std::string path = "assets/Player" + std::to_string(winner) + "BG.png";
        renderImage(path, WIN_WIDTH/2-350/2, 200);

        // Text inside box
        std::string text = "Player " + std::to_string(winner) + " wins!";
        TextTexture t = makeText(text, 35, 0, 0, 0);
        renderText(t, WIN_WIDTH/2-t.w/2, 200+300/2-t.h/2);
    }

    // Renders "game over" and instructions
    void RenderOutsideText()
    {
        // Game over message
        TextTexture t = makeText("Game Over", 55, 230, 230, 255);
        renderText(t, WIN_WIDTH/2-t.w/2, 50);

        // Instructions message
        t = makeText("Menu", 30, 210, 210, 235);
        int menuHeight = t.h;
        renderText(t, 50, WIN_HEIGHT-50-t.h);

        t = makeText("Again", 30, 210, 210, 235);
        int againWidth = t.w;
        renderText(t, 50, WIN_HEIGHT-50-t.h-menuHeight-10);

        t = makeText("\'B\'", 30, 210, 210, 235);
        renderText(t, 50+againWidth+50, WIN_HEIGHT-50-t.h);

        t = makeText("\'A\'", 30, 210, 210, 235);
        renderText(t, 50+againWidth+50, WIN_HEIGHT-50-t.h-menuHeight-10);
    }

    // Renders the Game Over screen
    void RenderGameOver()
    {
        SDL_RenderClear(renderer);

        RenderVictoryBox();
        RenderOutsideText();

        SDL_RenderPresent(renderer);
    }

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
						if (getPlayerNum(cnum))
							return OPTION_AGAIN;
					// Starts the game
					if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B)
						if (getPlayerNum(cnum))
							return OPTION_MENU;
					break;
				}
			}
		}
    }
};
