#include <iostream>
#include <string>
#include "sudoku.h"
#include "sudoku.cpp"

int main() {
    // initialize a sudoku
    Sudoku sudoku;

    // generate a sudoku
    sudoku.generate();

    // show the sudoku
    for(int i=0; i<9; i++) {
        cout << sudoku.matrix[i] << endl;
    }

    return 0;
}
