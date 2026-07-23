#ifndef GAME_HPP
#define GAME_HPP

#include "Snake.hpp"

#include <iostream>
#include <string>

class Game {
    private: 
    int width = 20;
    int height = 8;

    int score = 0;
    bool game_over = false;

    Snake snake;
    Position food;

    public:

    Game();
    void run();
    void drawBoard();
    bool is_gameover();
    int getScore();
    void spawnFood();

};

#endif