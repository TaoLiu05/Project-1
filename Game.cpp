#include "Game.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>

Game::Game() {
    spawnFood();
};

void Game::run(){

    using namespace std::chrono_literals;

    while(!game_over){

        snake.move();

        checkCollision();

        checkFoodCollision();

        system("clear");

        drawBoard();

        std::this_thread::sleep_for(1s);
    }

    std::cout <<"Game Over!" <<std::endl;
}

void Game::drawBoard(){
    const std::vector<Position>& body = snake.getBody();
    Position head = snake.getHead();

    for(int i = 0; i < width+2; i++){
        std::cout << '#'; 
    }
    std::cout << std::endl;

    for(int row = 0; row < height; row++){
        std::cout << '#';
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
        } 
        std::cout <<'#';
        std::cout << '\n';
    }
    for(int i = 0; i < width+2; i++){
        std::cout << '#'; 
    }
    std::cout << '\n';
    std::cout <<"Score: "<< score << std::endl;
}

bool Game::is_gameover(){
    return game_over;
}

int Game:: getScore(){
    return score;
}

void Game:: spawnFood(){
    const std::vector<Position>& body = snake.getBody();
    bool valid_position;

    std::random_device rd;
    std:: mt19937 gen(rd());

    std::uniform_int_distribution<> x_distr( 0, width - 1 );
    std::uniform_int_distribution<> y_distr( 0, height - 1);

    do
    {
        valid_position = true;

        food.x = x_distr(gen);
        food.y = y_distr(gen);

        for(size_t i = 0; i < body.size(); i++){
            if(food == body[i]){
                valid_position = false;
                break;
            }

        }
    } while (!valid_position);
}

void Game::checkCollision(){
    Position head = snake.getHead();
    const std:: vector<Position>& body = snake.getBody();

    if(head.x < 0 || head.x >= width || head.y < 0 || head.y >= height){
        game_over = true;
        return;
    }

    for(size_t i = 1; i < body.size(); i++){
        if(head == body[i]){
            game_over = true;
            break;
        }
    }
}

void Game::checkFoodCollision(){
    Position head = snake.getHead();
    if(head == food){
        snake.grow();
        score++;
        spawnFood();
    }
}