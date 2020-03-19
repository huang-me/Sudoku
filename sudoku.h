#ifndef SUDOKU_H
#define SUDOKU_H

/***************************************************
 * Finish your .cpp according to this header file. *
 * You can modify this file if needed.             *
 ***************************************************/

#include <string>
using namespace std;
#define SIZE 81

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
    void readIn();
    void solve();
    void setBoard(const int set_board[]);

    // matrix index
    string matrix[100];
    string temp[100];

  private:
    void printSolve();
    // bool checkCorrect();
    bool checkQuestion();
    bool checkIndexCorrect(int index);
    void trace(int num);

    int _board[SIZE];
    int _zeronum;
    int _solvenum;
    int _solveboard[SIZE];

};

#endif // SUDOKU_H
