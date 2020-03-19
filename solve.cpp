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
    // int sol = sudoku.solve();
    // if(sol == 0) {

    //     // test whether there's still solution
    //     // for(int i=0;i<9;i++) {
    //     //     for(int j=0;j<9;j++) {
    //     //         for(int k=1;k<10;k++) {
    //     //             if(sudoku.exist[i][j][k] == 0) {
    //     //                 cout << "2" << endl;
    //     //                 return 0;
    //     //             }
    //     //         }
    //     //     }
    //     // }

    //     // show matrix
    //     cout << "1" << endl;
    //     for(int i=0; i<9; i++) {
    //         for(int col=0; col<9; col++) {
    //             cout << to_string(sudoku.intMatrix[i][col]);
    //             if(col < 8) cout << " ";
    //         }
    //         cout << endl;
    //     }

    // } 
    // else if(sol == -1) cout << "0" << endl;
    cout << "0";
    return 0;
}