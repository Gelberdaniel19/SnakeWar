#include "globals.hpp"
#include "title.hpp"
#include "game.hpp"

int main()
{
	// Initialize
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(0);

	// Load window and renderer
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, COLOR_BG, 255);

	// Load controllers
    for (int i = 0; i < SDL_NumJoysticks() && i < 8; i++) {
		if (SDL_IsGameController(i)) {
			controllers.at(i) = SDL_GameControllerOpen(i);
			std::cout << SDL_GameControllerMapping(controllers.at(i)) << std::endl;
		}
	}

	// Title screen
	TitleScreen* title = new TitleScreen();
	title->Start();
	delete title;

	// Main Game
	Game* game = new Game();
	game->Start();
	delete game;

	// Cleanup
	for (int i = 0; i < controllers.size(); i++)
		SDL_GameControllerClose(controllers.at(i));
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}
