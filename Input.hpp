#ifndef INPUT_HPP
#define INPUT_HPP

#include<termios.h>

class Input{
    private:
    termios original_terminal;

    public:
    Input();
    char getInput()const;
    ~Input();
};


#endif