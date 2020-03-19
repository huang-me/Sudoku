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
    for(int i=0; i<9; i++) {
        getline(cin, input);
        for(int col=0; col<9; col++) {
            int tmp = (int)input[col*2]-48;
            sudoku.intMatrix[i][col] = tmp;
        }
    }

    // solve the sudoku
    int sol = sudoku.solve();
    if(sol == 0) {

        // show matrix
        cout << "1" << endl;
        for(int i=0; i<9; i++) {
            for(int col=0; col<9; col++) {
                cout << sudoku.intMatrix[i][col];
                if(col < 8) cout << " ";
            }
            cout << endl;
        }

    } 
    else if(sol == -1) cout << "0" << endl;

    return 0;
}