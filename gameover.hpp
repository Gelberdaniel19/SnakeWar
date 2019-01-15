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
        SDL_Surface* surface = IMG_Load(path.c_str());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect{WIN_WIDTH/2-350/2, 200, 350, 300};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        // Text inside box
        TTF_Font* font = TTF_OpenFont("assets/upheavtt.ttf", 35);
        SDL_Color color = {0, 0, 0};
        std::string text = "Player " + std::to_string(winner) + " wins!";
        SDL_Surface* temp = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, temp);
        rect = {WIN_WIDTH/2-temp->w/2, 200+300/2-temp->h/2, temp->w, temp->h};
        SDL_RenderCopy(renderer, message, NULL, &rect);
        SDL_FreeSurface(temp);
        SDL_DestroyTexture(message);
        TTF_CloseFont(font);
    }

    // Renders "game over" and instructions
    void RenderOutsideText()
    {
        // Make fonts
        TTF_Font* font1 = TTF_OpenFont("assets/upheavtt.ttf", 55);
        SDL_Color color1 = {230, 230, 255};
        TTF_Font* font2 = TTF_OpenFont("assets/upheavtt.ttf", 30);
        SDL_Color color2 = {210, 210, 235};

        // Game over message
        SDL_Surface* temp = TTF_RenderText_Solid(font1, "Game Over", color1);
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, temp);
        SDL_Rect rect{WIN_WIDTH/2-temp->w/2, 50, temp->w, temp->h};
        SDL_RenderCopy(renderer, message, NULL, &rect);
        SDL_FreeSurface(temp);
        SDL_DestroyTexture(message);
        TTF_CloseFont(font1);

        // Instructions message
        temp = TTF_RenderText_Solid(font2, "Menu", color2);
        message = SDL_CreateTextureFromSurface(renderer, temp);
        rect = {50, WIN_HEIGHT-50-temp->h, temp->w, temp->h};
        int menuHeight = temp->h;
        SDL_RenderCopy(renderer, message, NULL, &rect);
        SDL_FreeSurface(temp);
        SDL_DestroyTexture(message);

        temp = TTF_RenderText_Solid(font2, "Again", color2);
        message = SDL_CreateTextureFromSurface(renderer, temp);
        rect = {50, WIN_HEIGHT-50-temp->h-menuHeight-10, temp->w, temp->h};
        int againWidth = temp->w;
        SDL_RenderCopy(renderer, message, NULL, &rect);
        SDL_FreeSurface(temp);
        SDL_DestroyTexture(message);

        temp = TTF_RenderText_Solid(font2, "\'B\'", color2);
        message = SDL_CreateTextureFromSurface(renderer, temp);
        rect = {50+againWidth+50, WIN_HEIGHT-50-temp->h, temp->w, temp->h};
        SDL_RenderCopy(renderer, message, NULL, &rect);
        SDL_FreeSurface(temp);
        SDL_DestroyTexture(message);

        temp = TTF_RenderText_Solid(font2, "\'A\'", color2);
        message = SDL_CreateTextureFromSurface(renderer, temp);
        rect = {50+againWidth+50, WIN_HEIGHT-50-temp->h-menuHeight-10, temp->w, temp->h};
        SDL_RenderCopy(renderer, message, NULL, &rect);
        SDL_FreeSurface(temp);
        SDL_DestroyTexture(message);
        TTF_CloseFont(font2);
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
