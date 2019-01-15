#pragma once
#include "globals.hpp"

class GameOver
{
private:
    int winner = -1;

    // Renders the Game Over screen
    void RenderGameOver();

public:
    // Main loop of the Game Over screen
    void Start(int winner);
}
