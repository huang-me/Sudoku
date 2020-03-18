#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include "sudoku.h"
using namespace std;

Sudoku::Sudoku() {
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            for(int k=0; k<9; k++){
                exist[i][j][k] = 0;
                existSave[i][j][k] = 0;
            }
        }
    }
}

void Sudoku::generate() {
    // initialize the matrix to zero
    for(int row=0; row<9; row++) {
        matrix[row] = "0 0 0 0 0 0 0 0 0";
    }
    // give the matrix some value
    matrix[0][0] = '3';
    matrix[0][4] = '2';
    matrix[0][10] = '5';
    matrix[0][12] = '6';
    matrix[0][14] = '9';
    matrix[1][2] = '4';
    matrix[1][8] = '9';
    matrix[1][10] = '6';
    matrix[1][14] = '3';
    matrix[2][2] = '5';
    matrix[2][10] = '8';
    matrix[3][0] = '1';
    matrix[3][2] = '9';
    matrix[3][8] = '8';
    matrix[3][12] = '7';
    matrix[3][16] = '3';
    matrix[5][0] = '5';
    matrix[5][4] = '7';
    matrix[5][8] = '3';
    matrix[5][14] = '6';
    matrix[5][16] = '1';
    matrix[6][6] = '8';
    matrix[6][14] = '2';
    matrix[7][2] = '8';
    matrix[7][6] = '9';
    matrix[7][8] = '6';
    matrix[7][14] = '7';
    matrix[8][2] = '6';
    matrix[8][4] = '5';
    matrix[8][6] = '7';
    matrix[8][12] = '3';
    matrix[8][16] = '9';

    // copy to temp
    for(int i=0; i<9; i++) {
        temp[i] = matrix[i];
    }

    // get some random rotate or changes
    srand(time(NULL));
    int times = rand()%3+2;
    for(int i=0; i<times; i++) {
        int random = rand()%5+1;
        if(random == 1) {
            int ran1 = rand()%9, ran2 = rand()%9;
            swapNum(ran1, ran2);
        } else if(random == 2) {
            int ran1 = rand()%3, ran2 = rand()%3;
            swapRow(ran1, ran2);
        } else if(random == 3) {
            int ran1 = rand()%3, ran2 = rand()%3;
            swapCol(ran1, ran2);
        } else if(random == 4) {
            int time = rand()%4;
            rotate(time);
        } else {
            int kind = rand()%2;
            flip(kind);
        }
    }

}

void Sudoku::swapNum(char x, char y) {
    for(int row=0; row<9; row++) {
        for(int col=0; col<17; col+=2) {
            if(matrix[row][col] == x) matrix[row][col] = y;
            else if(matrix[row][col] == y) matrix[row][col] = x;
        }
    }

    for(int irow=0; irow<9; irow++) {
        temp[irow] = matrix[irow];
    }
}

void Sudoku::swapRow(int row1, int row2) {
    if(row1 == 1) row1 = 3;
    else if(row1 == 2) row1 = 6;
    else row1 = 0;
    if(row2 == 1) row2 = 3;
    else if(row2 == 2) row2 = 6;
    else row2 = 0;
    string tmp;
    for(int i=0; i<3; i++) {
        tmp = matrix[row2+i];
        matrix[row2+i] = matrix[row1+i];
        matrix[row1+i] = tmp;
    }

    for(int irow=0; irow<9; irow++) {
        temp[irow] = matrix[irow];
    }
}

void Sudoku::swapCol(int col1, int col2) {
    if(col1 == 1) col1 = 6;
    else if(col1 == 2) col1 = 12;
    else col1 = 0;
    if(col2 == 1) col2 = 6;
    else if(col2 == 2) col2 = 12;
    else col2 = 0;
    char tmp;
    for(int j=0; j<9; j++) {
        for(int i=0; i<5; i+=2) {
            tmp = matrix[j][col2+i];
            matrix[j][col2+i] = matrix[j][col1+i];
            matrix[j][col1+i] = tmp;
        }
        temp[j] = matrix[j];
    }
}

void Sudoku::rotate(int time) {
    time %= 4;
    for(int k=0; k<time; k++) {
        for(int row=0; row<9; row++) {
            for(int col=0; col<17; col+=2) {
                matrix[col/2][(8-row)*2] = temp[row][col];
            }
        }
        for(int irow=0; irow<9; irow++) {
            temp[irow] = matrix[irow];
        }
    }
}

void Sudoku::flip(int kind) {
    // up-down flip
    if(kind == 0) {
        for(int row=0; row<9; row++) {
            matrix[row] = temp[8-row];
        }
    }
    // left-right flip
    else if(kind == 1) {
        for(int row=0; row<9; row++) {
            for(int col=0; col<17; col+=2) {
                matrix[row][col] = temp[row][16 - col];
            }
        }
    }

    for(int irow=0; irow<9; irow++) {
        temp[irow] = matrix[irow];
    }
}

int Sudoku::solve() {
    rowPos = -1;
    colPos = -1;

    // find the first space
    for(int row=0; row<9; row++) {
        for(int col=0; col<9; col++) {
            if(intMatrix[row][col] == 0) {
                rowPos = row;
                colPos = col;
                break;
            }
        }
        if(rowPos != -1 && colPos != -1) break;
    }

    // find the num in the same row
    for(int i=1; i<10; i++) {
        if(exist[rowPos][colPos][intMatrix[rowPos][i]] != 1) exist[rowPos][colPos][intMatrix[rowPos][i]] = 1;
        if(exist[rowPos][colPos][intMatrix[i][colPos]] != 1) exist[rowPos][colPos][intMatrix[i][colPos]] = 1;
        if(existSave[rowPos][colPos][intMatrix[rowPos][i]] != 1) exist[rowPos][colPos][intMatrix[rowPos][i]] = 1;
        if(existSave[rowPos][colPos][intMatrix[i][colPos]] != 1) exist[rowPos][colPos][intMatrix[i][colPos]] = 1;
    }

    // set the start row or column
    if(rowPos < 3) rowstart = 0;
    else if(rowPos > 2 && rowPos < 6) rowstart = 3;
    else rowstart = 6;
    if(colPos < 3) colstart = 0;
    else if(colPos > 2 && colPos < 6) colstart = 3;
    else colstart = 6;

    // find the block
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(exist[rowPos][colPos][intMatrix[rowstart+i][colstart+i]] != 1) exist[rowPos][colPos][intMatrix[rowstart+i][colstart+i]] = 1;
        }
    }
    for(int i=1;i<10;i++) {
        cout << i << ":" << exist[rowPos][colPos][i] << " ";
    }
    cout << "row and col\t" << rowPos << "," << colPos << endl;
    // recursive the problem
    for(int i=1;i<10;i++) {
        int end = -1;
        // cout << rowPos << "&" << colPos << "*" << i << endl;
        // for(int i=1;i<10;i++) {
        //     cout << i << ":" << exist[rowPos][colPos][i] << " ";
        // }
        // cout << "row and column" << rowPos << colPos << endl;
        if(exist[rowPos][colPos][i] != 1) {
            intMatrix[rowPos][colPos] = i;
            exist[rowPos][colPos][i] = 1;
            
            if(finish()) 
                return 1;
            else {
                end = solve();
                if(end == 0) {
                    intMatrix[rowPos][colPos] = 0;
                    continue;
                }
                else return 1;
            }
        }
    }
    for(int i=1;i<10;i++){
        exist[rowPos][colPos][i] = existSave[rowPos][colPos][i];
    }
    return 0;
}

int Sudoku::finish() {
    int count = 0;
    for(int row=0; row<9; row++) {
        for(int col=0; col<9; col++) {
            if(intMatrix[row][col] == 0) count++;
        }
    }

    if(count) return 0;
    else return 1;
}