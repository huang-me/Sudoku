#include <iostream>
#include <string>
#include "sudoku.h"
#include "sudoku.cpp"
using namespace std;

int main() {
    Sudoku Sudoku;
    string input;
    int count=0;

    // read the file until 0
    getline(cin, input);
    while(input != "0") {
        Sudoku.matrix[count] = input;
        Sudoku.temp[count++] = input;
        getline(cin, input);
    }

    for(int i=9; i<count; i++) {
        // 1: swap two num
        if(Sudoku.matrix[i][0] == '1') {
            char num1 = Sudoku.matrix[i][2], num2 = Sudoku.matrix[i][4];
            Sudoku.swapNum(num1, num2);
        }
        // 2: swap two big rows
        else if(Sudoku.matrix[i][0] == '2') {
            char row1 = Sudoku.matrix[i][2], row2 = Sudoku.matrix[i][4];
            int irow1 = (int)row1-48, irow2 = (int)row2-48;
            Sudoku.swapRow(irow1, irow2);
        }
        // 3. swap two big columns
        else if(Sudoku.matrix[i][0] == '3') {
            char col1 = Sudoku.matrix[i][2], col2 = Sudoku.matrix[i][4];
            int icol1 = (int)col1-48, icol2 = (int)col2-48;
            Sudoku.swapCol(icol1, icol2);
        }
        // 4. rotate 90 degree for several times
        else if(Sudoku.matrix[i][0] == '4') {
            int time = (int)Sudoku.matrix[i][2] - 48;
            Sudoku.rotate(time);
        }
        // 5. up-down or left-right flip
        else if(Sudoku.matrix[i][0] == '5') {
            int kind = (int)Sudoku.matrix[i][2] - 48;
            Sudoku.flip(kind);
        }
    }


    // show output matrix
    for(int i=0; i<9; i++) {
        cout << Sudoku.matrix[i] << endl;
    }
    return 0;
}
