#include "Input.hpp"

#include<termios.h>
#include<unistd.h>
#include<fcntl.h>

Input::Input(){
    //save the current terminal settings.
    tcgetattr(STDIN_FILENO, &original_terminal);

    //make a copy that would be modified.
    termios current = original_terminal;

    //Disable canonical mode and echo so key presses are read
    //immediately and are not displayed.
    current.c_lflag &= ~(ICANON | ECHO);

    //Apply the modifed settings immdiately.
    tcsetattr(STDIN_FILENO, TCSANOW, &current);

    //Get the current file status flags.
    int flags = fcntl(STDIN_FILENO, F_GETFL);

    //Set the file status flags to the old flags plus the O_NONBLOCK flag.
    fcntl(STDIN_FILENO,F_SETFL,flags | O_NONBLOCK);
}

char Input:: getInput()const{
    char input;

    //Attempt to read a single key press.
    int attempt = read(STDIN_FILENO,&input, 1);

    //Return the key if one was read.
    if(attempt == 1){
        return input;
    }
    //No key was pressed.
    return '\0';
}

Input::~Input(){
    //Restore the original terminal settings.
    tcsetattr(STDIN_FILENO,TCSANOW,&original_terminal);
}

