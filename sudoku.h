#ifndef SUDOKU_H
#define SUDOKU_H

/***************************************************
 * Finish your .cpp according to this header file. *
 * You can modify this file if needed.             *
 ***************************************************/

#include <string>
using namespace std;

class Sudoku {
  public:
    Sudoku();

    // generate
    void generate();

    // transform
    void swapNum(char x, char y);
    void swapRow(int x, int y);
    void swapCol(int x, int y);
    void rotate(int x);
    void flip(int x);

    // solve
    int solve();

    // matrix index
    string matrix[100];
    string temp[100];
    int intMatrix[9][9], ans[9][9];
    int exist[9][9][10];
    int rowstart, colstart;
    int zeros[81];

};

#endif // SUDOKU_H
