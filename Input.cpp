#include "Input.hpp"

#include<termios.h>
#include<unistd.h>
#include<fcntl.h>

Input::Input(){
    //save the current terminal settings
    tcgetattr(STDIN_FILENO, &original_terminal);

    //make a copy that would be modified
    termios current = original_terminal;

    //Disable canonical mode and echo
    current.c_lflag &= ~(ICANON | ECHO);

    //Apply the modifed settings immdiately
    tcsetattr(STDIN_FILENO, TCSANOW, &current);

    //Get the file status flags for standard input
    int flags = fcntl(STDIN_FILENO, F_GETFL);

    //Set the file status flags to the old flags plus the O_NONBLOCK flag
    fcntl(STDIN_FILENO,F_SETFL,flags | O_NONBLOCK);
}

char Input:: getInput()const{
    char input;
    int attempt = read(STDIN_FILENO,&input, 1);

    if(attempt == 1){
        return input;
    }
    else{
        return '\0';
    }
}

Input::~Input(){
    tcsetattr(STDIN_FILENO,TCSANOW,&original_terminal);
}

