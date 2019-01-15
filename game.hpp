#pragma once
#include "globals.hpp"
#include <random>

struct Point
{
    int x = 0;
    int y = 0;
};

struct Player
{
    bool alive = true;
    int direction;
    std::vector<Point> snake;
    Player(int direction, int x, int y)
    {
        this->direction = direction;
        for (int i = 0; i < STARTING_TAIL; i++)
            snake.emplace_back(Point{x, y});
    }
};

class Game
{
private:
    std::vector<Player> players;
    std::vector<Point> walls, food;
    int numPlayers = playerCount();
    int tick = 0;
    bool playing = true;
    int winner = -1;

    // Read input and adjust player objects accordingly
    void HandleInput()
    {
    	SDL_Event e;
        while(SDL_PollEvent(&e)){
            switch(e.type){
    		case SDL_QUIT:
    			running = false;
    			break;

            case SDL_CONTROLLERBUTTONDOWN:
                int player = getPlayerNum((int)e.cbutton.which);
                if (players.at(player-1).direction != DIR_DOWN && e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)
                    players.at(player-1).direction = DIR_UP;
                else if (players.at(player-1).direction != DIR_UP && e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
                    players.at(player-1).direction = DIR_DOWN;
                else if (players.at(player-1).direction != DIR_RIGHT && e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
                    players.at(player-1).direction = DIR_LEFT;
                else if (players.at(player-1).direction != DIR_LEFT && e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
                    players.at(player-1).direction = DIR_RIGHT;
                break;
            }
        }
    }

    // Checks if a tile on the map is occupied by a snake
    bool IsEmpty(int x, int y)
    {
        for (Player pl : players)
            for (Point p : pl.snake)
                if (p.x == x && p.y == y)
                    return false;
        return true;
    }

    // Checks if the game is over and sets the winner
    bool IsGameOver()
    {
        // Put alive players into a list of numbers
        std::vector<int> aliveplayers;
        for (int i = 0; i < players.size(); i++) {
            if (players.at(i).alive) {
                aliveplayers.emplace_back(i+1);
            }
        }

        // If the game is over, set the winner to the player number
        // which is alive, otherwise -1.
        if (aliveplayers.size() == 0 || numPlayers != 1 && aliveplayers.size() == 1) {
            playing = false;
            winner = aliveplayers.size() == 1 ? aliveplayers.at(0) : -1;
            return true;
        }

        return false;
    }

    // Return a vector of the tiles which would kill the player
    std::vector<Point> GetKillTiles()
    {
        std::vector<Point> hitbox;

        // Add walls
        for (Point p : walls) {
            hitbox.emplace_back(p);
        }

        // Add players
        for (Player pl : players) {
            for (int i = 0; i < pl.snake.size(); i++) {
                hitbox.emplace_back(pl.snake.at(i));
            }
        }

        return hitbox;
    }

    // Moves all players and kills if they hit a kill tile
    void MoveAndCollide(std::vector<Point> killTiles)
    {
        for (int i = 0; i < players.size(); i++) {
            if (!players.at(i).alive) continue;

            for (int j = players.at(i).snake.size(); j > 1; j--)
                players.at(i).snake.at(j-1) = players.at(i).snake.at(j-2);
            if (players.at(i).direction == DIR_RIGHT) players.at(i).snake.at(0).x += 1;
            if (players.at(i).direction == DIR_LEFT) players.at(i).snake.at(0).x -= 1;
            if (players.at(i).direction == DIR_UP) players.at(i).snake.at(0).y -= 1;
            if (players.at(i).direction == DIR_DOWN) players.at(i).snake.at(0).y += 1;

            // Collision
            for (Point p : killTiles) {
                if (players.at(i).snake.at(0).x == p.x && players.at(i).snake.at(0).y == p.y) {
                    players.at(i).snake.clear();
                    players.at(i).alive = false;
                    break;
                }
            }
        }
    }

    // Checks if each food is being eaten, and elongates the snake.
    void EatFood()
    {
        for (int i = 0; i < food.size(); i++) {
            for (int j = 0; j < players.size(); j++) {
                if (players.at(j).alive && food.at(i).x == players.at(j).snake.at(0).x && food.at(i).y == players.at(j).snake.at(0).y) {
                    for (int k = 0; k < TAIL_GAIN; k++)
                        players.at(j).snake.emplace_back(players.at(j).snake.at(players.at(j).snake.size()-1));
                    food.erase(food.begin()+i);
                    i--;
                    break;
                }
            }
        }
    }

    // Randomly spawns a food
    void AddFood()
    {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 38);
        int x, y;
        do {
            x = dist(rng);
            y = dist(rng);
        } while (!IsEmpty(x, y));
        food.emplace_back(Point{x, y});
    }

    // Update game logic every tick
    void Update()
    {
        // End if the game is over
        if (IsGameOver()) return;

        // Movement and collision
        MoveAndCollide(GetKillTiles());

        // Check if food is being eaten
        EatFood();

        // Spawn food every some ticks.
        if (tick % (24/numPlayers) == 0)
            AddFood();
        tick++;
    }

    // Draws the game every tick
    void Render()
    {
        // Walls
        SDL_SetRenderDrawColor(renderer, COLOR_WALL, 255);
        for (int i = 0; i < walls.size(); i++) {
            SDL_Rect rect{walls.at(i).x*20, walls.at(i).y*20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }

        // Food
        SDL_SetRenderDrawColor(renderer, COLOR_FOOD, 255);
        for (int i = 0; i < food.size(); i++) {
            SDL_Rect rect{food.at(i).x*20, food.at(i).y*20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }

        // Players 1-4
        SDL_SetRenderDrawColor(renderer, COLOR_P1, 255);
        for (int i = 0; players.size() >= 1 && i < players.at(0).snake.size(); i++) {
            SDL_Rect rect{players.at(0).snake.at(i).x*20, players.at(0).snake.at(i).y*20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }
        SDL_SetRenderDrawColor(renderer, COLOR_P2, 255);
        for (int i = 0; players.size() >= 2 && i < players.at(1).snake.size(); i++) {
            SDL_Rect rect{players.at(1).snake.at(i).x*20, players.at(1).snake.at(i).y*20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }
        SDL_SetRenderDrawColor(renderer, COLOR_P3, 255);
        for (int i = 0; players.size() >= 3 && i < players.at(2).snake.size(); i++) {
            SDL_Rect rect{players.at(2).snake.at(i).x*20, players.at(2).snake.at(i).y*20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }
        SDL_SetRenderDrawColor(renderer, COLOR_P4, 255);
        for (int i = 0; players.size() == 4 && i < players.at(3).snake.size(); i++) {
            SDL_Rect rect{players.at(3).snake.at(i).x*20, players.at(3).snake.at(i).y*20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_SetRenderDrawColor(renderer, COLOR_BG, 255);
    }

public:
    // Starts the game and returns the player that wins. If only
    // one is playing, then it returns -1.
    int Start()
    {
        // Walls
        for (int i = 0; i < 40; i++) {
            walls.emplace_back(Point{0, i});
            walls.emplace_back(Point{i, 0});
            walls.emplace_back(Point{39, i});
            walls.emplace_back(Point{i, 39});
        }

        // Spawn snakes
        players.emplace_back(DIR_RIGHT, 13, 13);
        if (numPlayers >= 2)
            players.emplace_back(DIR_DOWN, 26, 13);
        if (numPlayers >= 3)
            players.emplace_back(DIR_UP, 13, 26);
        if (numPlayers == 4)
            players.emplace_back(DIR_LEFT, 26, 26);

        // Game loop
        while (running && playing) {
    		HandleInput();
    		SDL_RenderClear(renderer);
    		Update();
            Render();
    		SDL_RenderPresent(renderer);
    		SDL_Delay(1000/12);
    	}

        return winner;
    }
};
