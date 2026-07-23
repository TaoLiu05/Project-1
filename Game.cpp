#include "Game.hpp"
#include <iostream>
#include <random>

Game::Game() {
    spawnFood();
};

void Game::run(){
    drawBoard();
}

void Game::drawBoard(){
    const std::vector<Position>& body = snake.getBody();
    Position head = snake.getHead();

    for(int row = 0; row < height; row++){
        for(int column = 0; column < width; column++){
            Position current;
            current.x = column;
            current.y = row;

            if (current == head){
                std::cout <<'@';
            }
            else if(current == food){
                std::cout <<'F';
            }
            else{
                bool isBody = false;
                for(size_t i= 1; i < body.size();i++){
                    if(current == body[i]){
                        isBody = true;
                        break;
                    }
                }
                if(isBody){
                    std::cout << 'o';
                }
                else{
                    std::cout << '.';
                }

            }
        } std::cout << '\n';
        
    }
}

bool Game::is_gameover(){
    return game_over;
}

int Game:: getScore(){
    return score;
}

void Game:: spawnFood(){
    std::random_device rd;
    std:: mt19937 gen(rd());

    std::uniform_int_distribution<> x_distr( 0, width - 1 );
    std::uniform_int_distribution<> y_distr( 0, height - 1);

    food.x = x_distr(gen);
    food.y = y_distr(gen);
}
