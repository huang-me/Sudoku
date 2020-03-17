#include <iostream>
#include <string>
#include "sudoku.h"
using namespace std;

Sudoku::Sudoku() {
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