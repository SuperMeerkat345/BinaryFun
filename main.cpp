#include <iostream>
#include <ctime>
#include "src/Grid.hpp"
#include <string>

#include <termios.h>
#include <unistd.h>

// input without enter key function
char getch() {
    char buf = 0;
    struct termios old = {};
    fflush(stdout);

    if (tcgetattr(STDIN_FILENO, &old) < 0)
        perror("tcgetattr()");

    struct termios newt = old;
    newt.c_lflag &= ~(ICANON | ECHO); // disable buffering + echo
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) < 0)
        perror("tcsetattr ICANON");

    if (read(STDIN_FILENO, &buf, 1) < 0)
        perror("read()");

    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return buf;
}


int main() {
    srand(static_cast<unsigned int>(time(NULL))); // seed random number generator
    
    char input;
    Grid grid = Grid();

    while (true) {
        grid.displayGrid();

        if (grid.isSolved()) {
            grid.win();
            std::cout << "\n\nPuzzle Solved! Press ';' to go to the next round or 'p' to quit.\n";
            std::cout << "Solving time: " << grid.getSolvingTime();
        }

        input = getch();
        if (!grid.processInput(input)) {
            break;
        }
    }

    return 0;
}
