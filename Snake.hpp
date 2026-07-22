#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "position.hpp"
#include<vector>

class Snake {
    private:
    std::vector<Position> body;

    bool pending_growth = false;

    public:

    enum Direction{
        Up,
        Down,
        Right,
        Left
    };

    Direction current_direction;

    Snake();

    void move();

    void grow();

    void change_direction(Direction new_direction);

};

#endif

