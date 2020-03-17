#include <iostream>
#include <string>
#include "sudoku.h"
#include "sudoku.cpp"
using namespace std;

int main() {
    // initialize sudoku
    Sudoku sudoku;
    string input;

    // get the input
    for(int i=0;i<9;i++) {
        getline(cin, input);
        for(int col=0;col<9;col++){
            int tmp = (int)input[col*2]-48;
            sudoku.intMatrix[i][col] = tmp;
        }
    }

    // solve the sudoku
    sudoku.solve();

    // show matrix
    for(int i=0;i<9;i++) {
        for(int col=0;col<9;col++) {
            cout << sudoku.intMatrix[i][col];
        }
        cout << endl;
    }
    return 0;
}