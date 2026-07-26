#include "Game.hpp"
#include "Input.hpp"
#include "color.hpp"

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>

Game::Game() {
    //Initialize the game state 
    resetGame();
};

void Game::run(){

    using namespace std::chrono_literals;

    //Game will keep running until the player chooses to quit.
    while(running){

        resetGame();

        std::chrono::steady_clock::time_point last_move_time = 
        std::chrono::steady_clock::now();

        //Draws the intia; game board.
        system("clear");
        drawBoard();
        printControls();

        while(!game_over){

            handleInputs();

            auto current_time = std::chrono::steady_clock:: now();
            auto elapsed_time = current_time - last_move_time;

            //Update the game when enough time has passed.
            if(elapsed_time >= move_delay){

                snake.move();

                checkCollision();

                checkFoodCollision();

                //Updates the game state by redrawing the board.
                system("clear");
                drawBoard();

                if(!game_over){
                    printControls();
                }
            
                last_move_time = current_time;
            }
        }
        printGameOver();

        bool waiting = true;

        //Post gameover screen where it waits for the player to restart or quit.
        while(waiting){
            char key = input.getInput();

            switch(key){
                case 'r':
                case 'R': {
                    waiting = false;
                    break;
                }
                case 'q':
                case 'Q': {
                    waiting = false;
                    running = false;
                    break;
                }
            }

            //Prevent unnecessary CPU usage while waiting.
            std::this_thread::sleep_for(10ms);
        }
    }
}

void Game::drawBoard(){
    const std::vector<Position>& body = snake.getBody();
    Position head = snake.getHead();

    //Draw the top border of the board.
    for(int i = 0; i < width+2; i++){
        std::cout << Colors::CYAN << '#' << Colors::RESET; 
    }
    std::cout << std::endl;

    //Draw each row of the game board.
    for(int row = 0; row < height; row++){

        //Draw the left border of the board.
        std::cout << Colors::CYAN << '#' << Colors::RESET;
        for(int column = 0; column < width; column++){
            Position current;
            current.x = column;
            current.y = row;

            if (current == head){
                std::cout << Colors::BRIGHT_GREEN <<'@'<< Colors::RESET;
            }
            else if(current == food){
                std::cout << Colors::RED <<'F' << Colors::RESET;
            }
            else{
                bool isBody = false;

                //Check if the current position is part of the snake's body.
                for(size_t i= 1; i < body.size();i++){
                    if(current == body[i]){
                        isBody = true;
                        break;
                    }
                }
                if(isBody){
                    std::cout << Colors::GREEN << 'o' << Colors::RESET;
                }
                else{
                    std::cout << '.';
                }

            }
        }

        //Draw the right border of the board.
        std::cout << Colors::CYAN << '#' << Colors::RESET;
        std::cout << '\n';
    }

    //Draw the bottom border.
    for(int i = 0; i < width+2; i++){
        std::cout << Colors::CYAN << '#' << Colors::RESET; 
    }
    std::cout << '\n';
    std::cout << Colors::YELLOW << "Score: " << score << Colors::RESET << std::endl;
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

    //Check if food generates on top of the snake and if it does, generates another position.
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

    //Check if the snake has hit a wall.
    if(head.x < 0 || head.x >= width || head.y < 0 || head.y >= height){
        game_over = true;
        return;
    }

    //Check if the snake has collided with its own body
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

        //After 3 food are eaten, speed up the snake until a certain threshold.
        if(score % 3 == 0){
            if(move_delay > minimum_move_delay){
                std::chrono::milliseconds delay_subtract{10};
                move_delay = move_delay - delay_subtract;
                if(move_delay < minimum_move_delay){
                    move_delay = minimum_move_delay;
                }
            }
        }
        spawnFood();
    }
}

void Game::handleInputs(){
    char key = input.getInput();

    switch(key){
        case 'w':{
            snake.change_direction(Up);
            break;
        }
        case 's':{
            snake.change_direction(Down);
            break;
        }
        case 'd':{
            snake.change_direction(Right);
            break;
        }
        case 'a':{
            snake.change_direction(Left);
            break;
        }
        default:{
        }
    }
}

void Game::resetGame(){
    score = 0;
    game_over = false;
    move_delay = starting_move_delay;
    snake = Snake();
    spawnFood();
}

void Game::printControls(){
    std::cout << "Controls: W A S D " << std::endl;
}

void Game::printGameOver(){
    std::cout << Colors::BRIGHT_RED<<"Game Over!" << Colors::RESET << std::endl;
    std::cout <<"Press R to" << Colors::ORANGE<<" Restart" << Colors:: RESET <<std::endl;
    std::cout <<"Press Q to" << Colors::BRIGHT_PURPLE <<" Quit" << Colors::RESET << std::endl;
}