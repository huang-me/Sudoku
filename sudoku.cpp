#include <iostream>
#include <string>
#include<cstring>
#include <algorithm>
// #include <iterator>
#include <cstdlib>
#include <ctime>
#include "sudoku.h"
using namespace std;

Sudoku::Sudoku() {
    int empty[SIZE];
    memset(empty,0,sizeof(empty));
    setBoard(empty);
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

void Sudoku::setBoard(const int set_board[]) {
    int i;
    for(i=0; i<SIZE; i++) {
        _board[i]=set_board[i];
    }
}

void Sudoku::printSolve() {
    //print out the answer which store in _solveboard[]
    int i;
    for(i=0; i<SIZE; i++) {
        cout<<_solveboard[i];
        cout<<(((i+1)%9==0)?'\n':' ');
    }
}

bool Sudoku::checkQuestion() {
    //because the question maybe wrong, solve after checking
    int i;
    for(i=0; i<SIZE; i++) {
        if(_board[i]!=0) {
            if(checkIndexCorrect(i)==false) {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::checkIndexCorrect(int index) {
    int col,row,cell,i,j;
    col=index%9;
    row=static_cast<int>(index/9);
    cell=(static_cast<int>(row/3))*3+(static_cast<int>(col/3));
    for(i=0,j=9*row; i<9; i++,j++) {
        if(_board[index]==_board[j]&&j!=index) {
            //if check index has the same number then return false
            return false;
        }
    }
    for(i=0,j=col; i<9; i++,j+=9) { //col check
        if(_board[index]==_board[j]&&j!=index) {
            //if check index has the same number then return false
            return false;
        }
    }
    switch(cell) { //cell check
    //using switch to get the cell's first index
    case 0:
    case 1:
    case 2:
        j=cell*3;
        break;
    case 3:
    case 4:
    case 5:
        j=cell*3+18;
        break;
    case 6:
    case 7:
    case 8:
        j=cell*3+36;
        break;
    }
    for(i=0,j; i<9; i++,j+=((j%3==2)?7:1)) {
        if(_board[index]==_board[j]&&j!=index) {
            //if check index has the same number then return false
            return false;
        }
    }
    return true;//if all correct return true
}

void Sudoku::trace(int num) {
    int i,solve_count=0;
    if(num==SIZE) { //trace finish
        for(i=0; i<SIZE; i++) {
            //store first solution to check have any other solution
            _solveboard[i]=_board[i];
        }
        _solvenum++;
        if(_solvenum>1) {
            //more than 1 solution
            return ;
        } else;
    }
    int col,row;
    col=num%9;
    row=static_cast<int>(num/9);
    if(_board[num]==0) { //find where can insert number
        for(i=1; i<=9; i++) {
            //insert number from 1 to 9
            _board[num]=i;
            if(checkIndexCorrect(num))
                trace(num+1);
        }
        _board[num]=0;//back to up one level's for loop
    } else {
        //if meet problem number, insert the next index
        trace(num+1);
    }
}

void Sudoku::readIn() {
    int i;
    int in_board[SIZE];
    _zeronum=0;
    for(i=0; i<SIZE; i++) {
        cin >> in_board[i];
        cout << in_board[i];
        if(i % 9 == 8) cout << endl;
        //count the zero's number
        if(in_board[i] == 0) {
            _zeronum++;
        }
    }
    setBoard(in_board);
}

void Sudoku::solve() {
    int solve_count=0;
    _solvenum=0;
    //there is more than 1 solution if numbers are less than 17
    if(checkQuestion()&&_zeronum>64) {
        cout<<2<<endl;
    } else if(checkQuestion()) {
        trace(0);
        solve_count++;
        switch(_solvenum) {
        case 0://no solution
            cout<<0;
            break;
        case 1://only 1 solution
            cout<<1<<endl;
            printSolve();
            break;
        default://more than 1 solution
            cout<<2;
            break;
        }
    } else {
        cout<<0;
    }
}
