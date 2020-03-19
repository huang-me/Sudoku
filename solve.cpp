#include "sudoku.h"
#include "sudoku.cpp"

int main() {
    Sudoku sudoku;
    sudoku.readIn();
    sudoku.solve();
    return 0;
}
