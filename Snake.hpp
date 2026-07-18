#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "position.hpp"
#include<vector>

class Snake {
    private:
    std::vector<Position> body;
    enum Direction{
        up,
        down,
        right,
        left
    };

    public:

    Snake();

    void move();

    void grow();

    void change_direction();

};

#endif

