#include "globals.hpp"
#include "title.hpp"
#include "game.hpp"

void LoadSDL()
{
	// Initialize
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(0);

	// Load window and renderer
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, COLOR_BG, 255);
}

void CleanSDL()
{
	// Cleanup
	for (int i = 0; i < controllers.size(); i++)
		SDL_GameControllerClose(controllers.at(i));
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

int main()
{
	LoadSDL();

	// Scene loop:
	// Game -> Game over -> Game
	//					 -> Title
	while (running) {
		TitleScreen* title = new TitleScreen();
		title->Start();
		delete title;

		Game* game = new Game();
		int winner = game->Start();
		delete game;
		std::cout << "Winner: " << winner << std::endl;
	}

	CleanSDL();
}
