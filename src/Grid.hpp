#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <array>

class Grid {
private:
    int grid[3][3] = {0};
    int solution[3][3] = {0};
    int solsX[3] = {0}, solsY[3] = {0};
    char keyBinds[3][3] = {
        {'q', 'w', 'e'},
        {'a', 's', 'd'},
        {'z', 'x', 'c'}
    };

    void randomize();
    void calculateSolutions();

    void clearMatrix(int matrix[][3]);
    void clearGrid();



public:
    Grid();
    ~Grid();

    void displayGrid();
    void nextRound();
    bool isSolved();
    bool processInput(char input);
};

#endif // GRID_HPP
