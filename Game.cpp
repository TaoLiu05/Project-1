#include "Game.hpp"
#include <iostream>

Game::Game() {
};

void Game::run(){
    drawBoard();
}

void Game::drawBoard(){
    for(int row = 0; row < height; row++){
        for(int column = 0; column < width; column++){
            std::cout << ".";
        }
        std::cout << std::endl;
    }
}

bool Game::is_gameover(){
    return game_over;
}

int Game:: getScore(){
    return score;
}







