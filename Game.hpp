#ifndef GAME_HPP
#define GAME_HPP

#include "Snake.hpp"
#include "Input.hpp"
#include "direction.hpp"

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

class Game {
    private: 
    int width = 20;
    int height = 10;

    int score = 0;
    bool game_over = false;
    bool running = true;

    std::chrono::milliseconds starting_move_delay{300};
    std::chrono::milliseconds move_delay{starting_move_delay};
    std::chrono::milliseconds minimum_move_delay{75};

    Snake snake;
    Position food;
    Input input;

    public:

    Game();
    void run();
    void drawBoard();
    bool is_gameover();
    int getScore();
    void spawnFood();
    void checkCollision();
    void checkFoodCollision();
    void handleInputs();
    void resetGame();
    void printControls();
    void printGameOver();

};

#endif