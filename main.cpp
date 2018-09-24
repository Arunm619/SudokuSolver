#include "SudokuSolver.cpp"

#define easy "easy.txt"
#define medium "medium.txt"
#define hard "hard.txt"

int main() {


    SudokuSolver mySolver;

    //change the level of difficulty here.
    //easy, medium, hard

    mySolver.chooseBoard(medium);

    mySolver.solve();

    return 0;
}