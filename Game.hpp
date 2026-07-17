#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>


class Game {
    private: 
    int width = 20;
    int height = 8;

    int score = 0;
    bool game_over = false;

    int food_position_x;
    int food_position_y;

    public:
    Game();
    void run();
    void drawBoard();
    bool is_gameover();
    int getScore();

};

#endif