#include "Grid.hpp"

// CONSTRUCTOR

Grid::Grid() {
    nextRound();
}
Grid::~Grid() {}

// PRIVATE

// zeroes the input matrix
void Grid::clearMatrix(int matrix[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = 0;
        }
    }
}
// clears the display grid
void Grid::clearGrid() {
    clearMatrix(grid);
}

// sets the time of start
void Grid::setStartTime() {
    startTime = std::chrono::steady_clock::now();
}

// resets solution grid
// then selects 4 random elements in the grid and sets them to ones
// algorithm only works for 3x3 grids, otherwise you must modify the numbers
// this took way too long to code...
void Grid::randomize() {
    clearMatrix(solution); // reset solution matrix

    int seenIndex[4] = {-1, -1, -1, -1}; // keep track of index that was already activated

    for (int n = 0; n < 4; n++) { // repeat 4 times for the 4 selected indecies 
        int randIndex = rand() % (9-n); // decrease range for each selected     
        //std::cout << randIndex << std::endl;
        int temp = randIndex; // remember randIndex for later
        
        int x = 0;
        int y = 0;
        int i = 0;

        // while we havent reached the random index and while the index isnt already selected
        while (randIndex != 0 || std::find(std::begin(seenIndex), std::end(seenIndex), i) != std::end(seenIndex)) {
            if (x < 2) { // if we arent about to overflow advance an x
                x++;
            }
            else { // if overflowing, go to next row, reset x
                y++;
                x=0;
            }

            // if this index is in the seen indecies, skip it
            if (std::find(std::begin(seenIndex), std::end(seenIndex), i) != std::end(seenIndex)) {
                i++;
                continue; // skip 
            }                
            else {
                i++;
                randIndex--;
            }
        }

        solution[y][x] = 1; // set the index to selected 
        seenIndex[n] = i; // remember that this index has already been selected
    }
}

// calculates the solutions for solsX and solsY
// where X is from left to right
// and Y is top to bottom
void Grid::calculateSolutions() {
    for (int y = 0; y < 3; y++) {
        solsY[y] = solution[y][0]*4 + solution[y][1]*2 + solution[y][2]*1; // formula for binary to decimal
    }

    for (int x = 0; x < 3; x++) {
        solsX[x] = solution[0][x]*4 + solution[1][x]*2 + solution[2][x]*1; // formula for binary to decimal
    }
}
// PUBLIC

// prints the display grid
void Grid::displayGrid() {
    // set grid to solution for testing and debuging:
    //for (int y = 0; y < 3; y++) {
    //    for (int x = 0; x < 3; x++) {
    //        grid[y][x] = solution[y][x];
    //    }
    //}

    std::cout << "\033[2J\033[1;1H" << std::flush; // clear terminal
    std::cout << "\n";

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            std::cout << "[" << grid[y][x] << "]"; // grid
        }
        std::cout << " [" << solsY[y] << "] "; // horiz sols
        std::cout << "\n";
    }   
    std::cout << "\n";

    // for the last row, display the vert solutions
    for (int x = 0; x < 3; x++) {
        std::cout << "[" << solsX[x] << "]";
    }

    std:: cout << " ";
}

// does all the logic and resetting needed to 
// reset the game and go to the next round
void Grid::nextRound() {
    randomize();
    calculateSolutions();

    clearGrid();
    setStartTime();
}

// returns true if grid == solution
// else returns false
bool Grid::isSolved() {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (grid[y][x] != solution[y][x]) {
                return false;
            }
        }
    }

    return true;
}

// gets the amount of time in between the start of solving and now
std::chrono::milliseconds Grid::getSolvingTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(solveTime - startTime).count();
}

// processes user input to modify the grid
// return false to stop the proces
// return true to continue
bool Grid::processInput(char input) {
    if (input == 'p') { // quit case
        return false;
    } 
    if (input == ';' && isSolved()) { // next round case
        nextRound();
    }    

    if (isSolved()) { // if already solved, ignore other inputs
        return true;
    }

    // process grid input
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (input == keyBinds[y][x]) {
                grid[y][x] = (grid[y][x] + 1) % 2; // toggle between 0 and 1
            }
        }
    }   

    return true;
}

// sets the solveTime
void Grid::win() {
    solveTime = std::chrono::steady_clock::now();
}