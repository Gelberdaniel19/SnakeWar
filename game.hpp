#pragma once
#include "globals.hpp"
#include <random>

struct Point
{
    int x = 0;
    int y = 0;
};

struct Game
{
    // Controller states
    int playerDir1 = DIR_LEFT;
    int playerDir2 = DIR_LEFT;
    int playerDir3 = DIR_UP;
    int playerDir4 = DIR_LEFT;
    std::vector<Point> snake1, snake2, snake3, snake4, walls, food;
    int numPlayers = playerCount();
    int tick = 0;
    bool playing = true;
    bool alive1 = false;
    bool alive2 = false;
    bool alive3 = false;
    bool alive4 = false;

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
                if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
                    if (player == 1 && playerDir1 != DIR_DOWN) playerDir1 = DIR_UP;
                    if (player == 2 && playerDir2 != DIR_DOWN) playerDir2 = DIR_UP;
                    if (player == 3 && playerDir3 != DIR_DOWN) playerDir3 = DIR_UP;
                    if (player == 4 && playerDir4 != DIR_DOWN) playerDir4 = DIR_UP;
                } else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
                    if (player == 1 && playerDir1 != DIR_UP) playerDir1 = DIR_DOWN;
                    if (player == 2 && playerDir2 != DIR_UP) playerDir2 = DIR_DOWN;
                    if (player == 3 && playerDir3 != DIR_UP) playerDir3 = DIR_DOWN;
                    if (player == 4 && playerDir4 != DIR_UP) playerDir4 = DIR_DOWN;
                } else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
                    if (player == 1 && playerDir1 != DIR_RIGHT) playerDir1 = DIR_LEFT;
                    if (player == 2 && playerDir2 != DIR_RIGHT) playerDir2 = DIR_LEFT;
                    if (player == 3 && playerDir3 != DIR_RIGHT) playerDir3 = DIR_LEFT;
                    if (player == 4 && playerDir4 != DIR_RIGHT) playerDir4 = DIR_LEFT;
                } else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
                    if (player == 1 && playerDir1 != DIR_LEFT) playerDir1 = DIR_RIGHT;
                    if (player == 2 && playerDir2 != DIR_LEFT) playerDir2 = DIR_RIGHT;
                    if (player == 3 && playerDir3 != DIR_LEFT) playerDir3 = DIR_RIGHT;
                    if (player == 4 && playerDir4 != DIR_LEFT) playerDir4 = DIR_RIGHT;
                }
                break;
            }
        }
    }

    bool IsEmpty(int x, int y)
    {
        for (Point p : snake1)
            if (p.x == x && p.y == y)
                return false;
        for (Point p : snake2)
            if (p.x == x && p.y == y)
                return false;
        for (Point p : snake3)
            if (p.x == x && p.y == y)
                return false;
        for (Point p : snake4)
            if (p.x == x && p.y == y)
                return false;
        return true;
    }

    void Update()
    {
        // See if the game is over
        if (!(alive1 || alive2 || alive3 || alive4)) {
            playing = false;
            return;
        }

        // Mark the tiles which would kill the player
        std::vector<Point> hitbox;
        for (Point p : walls)
            hitbox.emplace_back(p);
        for (int i = 1; i < snake1.size(); i++)
            hitbox.emplace_back(snake1.at(i));
        for (int i = 1; i < snake2.size(); i++)
            hitbox.emplace_back(snake2.at(i));
        for (int i = 1; i < snake3.size(); i++)
            hitbox.emplace_back(snake3.at(i));
        for (int i = 1; i < snake4.size(); i++)
            hitbox.emplace_back(snake4.at(i));

        // Player 1 mvmt
        if (alive1) {
            for (int i = snake1.size(); i > 1; i--)
                snake1.at(i-1) = snake1.at(i-2);
            if (playerDir1 == DIR_RIGHT) snake1.at(0).x += 1;
            if (playerDir1 == DIR_LEFT) snake1.at(0).x -= 1;
            if (playerDir1 == DIR_UP) snake1.at(0).y -= 1;
            if (playerDir1 == DIR_DOWN) snake1.at(0).y += 1;
            for (Point p : hitbox) {
                if (snake1.at(0).x == p.x && snake1.at(0).y == p.y) {
                    snake1.clear();
                    alive1 = false;
                    if (numPlayers == 1)
                        playing = false;
                    break;
                }
            }
        }

        // Player 2 mvmt
        if (alive2) {
            for (int i = snake2.size(); i > 1; i--)
                snake2.at(i-1) = snake2.at(i-2);
            if (playerDir2 == DIR_RIGHT) snake2.at(0).x += 1;
            if (playerDir2 == DIR_LEFT) snake2.at(0).x -= 1;
            if (playerDir2 == DIR_UP) snake2.at(0).y -= 1;
            if (playerDir2 == DIR_DOWN) snake2.at(0).y += 1;
            for (Point p : hitbox) {
                if (snake2.at(0).x == p.x && snake2.at(0).y == p.y) {
                    snake2.clear();
                    alive2 = false;
                    break;
                }
            }
        }

        // Player 3 mvmt
        if (alive3) {
            for (int i = snake3.size(); i > 1; i--)
                snake3.at(i-1) = snake3.at(i-2);
            if (playerDir3 == DIR_RIGHT) snake3.at(0).x += 1;
            if (playerDir3 == DIR_LEFT) snake3.at(0).x -= 1;
            if (playerDir3 == DIR_UP) snake3.at(0).y -= 1;
            if (playerDir3 == DIR_DOWN) snake3.at(0).y += 1;
            for (Point p : hitbox) {
                if (snake3.at(0).x == p.x && snake3.at(0).y == p.y) {
                    snake3.clear();
                    alive3 = false;
                    break;
                }
            }
        }

        // Player 4 mvmt
        if (alive4) {
            for (int i = snake4.size(); i > 1; i--)
                snake4.at(i-1) = snake4.at(i-2);
            if (playerDir4 == DIR_RIGHT) snake4.at(0).x += 1;
            if (playerDir4 == DIR_LEFT) snake4.at(0).x -= 1;
            if (playerDir4 == DIR_UP) snake4.at(0).y -= 1;
            if (playerDir4 == DIR_DOWN) snake4.at(0).y += 1;
            for (Point p : hitbox) {
                if (snake4.at(0).x == p.x && snake4.at(0).y == p.y) {
                    snake4.clear();
                    alive4 = false;
                    break;
                }
            }
        }

        for (int i = 0; i < food.size();) {
            if (alive1 && food.at(i).x == snake1.at(0).x && food.at(i).y == snake1.at(0).y) {
                snake1.emplace_back(snake1.at(snake1.size()-1));
                food.erase(food.begin()+i);
            } else if (alive2 && food.at(i).x == snake2.at(0).x && food.at(i).y == snake2.at(0).y) {
                snake2.emplace_back(snake2.at(snake2.size()-1));
                food.erase(food.begin()+i);
            } else if (alive3 && food.at(i).x == snake3.at(0).x && food.at(i).y == snake3.at(0).y) {
                snake3.emplace_back(snake3.at(snake3.size()-1));
                food.erase(food.begin()+i);
            } else if (alive4 && food.at(i).x == snake4.at(0).x && food.at(i).y == snake4.at(0).y) {
                snake4.emplace_back(snake4.at(snake4.size()-1));
                food.erase(food.begin()+i);
            } else i++;
        }

        // Spawn food once per second
        if (tick % (24/numPlayers) == 0) {
            std::mt19937 rng;
            rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist(1, 38);
            int x, y;
            do {
                x = dist(rng);
                y = dist(rng);
            } while (!IsEmpty(x, y));
            food.emplace_back(Point{x, y});
            std::cout << "Food at " << x << ", " << y << std::endl;
        }
        tick++;
    }

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

        // Player1
        SDL_SetRenderDrawColor(renderer, COLOR_P1, 255);
        for (int i = 0; i < snake1.size(); i++) {
            SDL_Rect rect{snake1.at(i).x*20, snake1.at(i).y*20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }

        // Player2
        SDL_SetRenderDrawColor(renderer, COLOR_P2, 255);
        for (int i = 0; i < snake2.size(); i++) {
            SDL_Rect rect{snake2.at(i).x*20, snake2.at(i).y*20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }

        // Player3
        SDL_SetRenderDrawColor(renderer, COLOR_P3, 255);
        for (int i = 0; i < snake3.size(); i++) {
            SDL_Rect rect{snake3.at(i).x*20, snake3.at(i).y*20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }

        // Player4
        SDL_SetRenderDrawColor(renderer, COLOR_P4, 255);
        for (int i = 0; i < snake4.size(); i++) {
            SDL_Rect rect{snake4.at(i).x*20, snake4.at(i).y*20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_SetRenderDrawColor(renderer, COLOR_BG, 255);
    }

    void Start()
    {
        // Walls
        for (int i = 0; i < 40; i++) {
            walls.emplace_back(Point{0, i});
            walls.emplace_back(Point{i, 0});
            walls.emplace_back(Point{39, i});
            walls.emplace_back(Point{i, 39});
        }

        // Spawn snakes
        for (int i = 0; i < 5; i++)
            snake1.emplace_back(Point{13, 13});
        alive1 = true;
        if (numPlayers >= 2) {
            for (int i = 0; i < 5; i++)
                snake2.emplace_back(Point{26, 13});
            alive2 = true;
        }
        if (numPlayers >= 3) {
            for (int i = 0; i < 5; i++)
                snake3.emplace_back(Point{13, 26});
            alive3 = true;
        }
        if (numPlayers == 4) {
            for (int i = 0; i < 5; i++)
                snake3.emplace_back(Point{26, 26});
            alive4 = true;
        }

        // game loop
        while (running && playing) {
    		HandleInput();
    		SDL_RenderClear(renderer);
    		Update();
            Render();
    		SDL_RenderPresent(renderer);
    		SDL_Delay(1000/6);

            std::cout << "Player 1: " << playerDir1 << '\n';
            std::cout << "Player 2: " << playerDir2 << '\n';
            std::cout << "Player 3: " << playerDir3 << '\n';
            std::cout << "Player 4: " << playerDir4 << '\n';
            std::cout << "\n\n\n\n\n\n\n\n";
    	}
    }
};
