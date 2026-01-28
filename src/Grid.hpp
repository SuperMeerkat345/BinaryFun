#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <array>
#include <ctime>
#include <chrono>

class Grid {
private:
    int grid[3][3] = {0};
    int solution[3][3] = {0};
    int solsX[3] = {0}, solsY[3] = {0};
    std::chrono::_V2::steady_clock::time_point startTime;
    std::chrono::_V2::steady_clock::time_point solveTime;

    char keyBinds[3][3] = {
        {'q', 'w', 'e'},
        {'a', 's', 'd'},
        {'z', 'x', 'c'}
    };

    void randomize();
    void calculateSolutions();

    void clearMatrix(int matrix[][3]);
    void clearGrid();
    void setStartTime();



public:
    Grid();
    ~Grid();

    void displayGrid();
    void nextRound();
    bool isSolved();
    unsigned int getSolvingTime();
    bool processInput(char input);
    void win();
};

#endif // GRID_HPP
