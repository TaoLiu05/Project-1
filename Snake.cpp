#include "Snake.hpp"

Snake::Snake(){
    current_direction = Right;

    body = {
        {10,4},
        {9,4},
        {8,4}
    };
}

void Snake::move(){
    Position current_head = body.at(0);
    Position new_head;

    switch(current_direction){
        case Up:{
            new_head = current_head;
            new_head.y -= 1;
            break;
        }
        case Down:{
            new_head = current_head;
            new_head.y += 1;
            break;
        }
        case Right:{
            new_head = current_head;
            new_head.x += 1;
            break;
        }
        case Left:{
            new_head = current_head;
            new_head.x -= 1;
            break;
        }
    }
    body.insert(body.begin(),new_head);

    if(pending_growth){
        pending_growth = false;
    }
    else{
        body.pop_back();
    }
}

void Snake::grow(){
    pending_growth = true;
}

void Snake::change_direction(Direction new_direction ){
    switch(current_direction){

        case Up:{
            if(new_direction != Down){
                current_direction = new_direction;
            }
            break;
        }
        case Down:{
            if(new_direction != Up){
                current_direction = new_direction;
            }
            break;
        }
        case Right:{
            if(new_direction != Left){
                current_direction = new_direction;
            }
            break;
        }
        case Left:{
            if(new_direction != Right){
                current_direction = new_direction;
            }
            break;
        }
    }
}

Position Snake:: getHead() const{
    return body.at(0);
}

const std::vector<Position>& Snake::getBody() const{
    return body;
}










