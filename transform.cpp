#include <iostream>
#include <string>
using namespace std;

int main() {
    // finish your transform code...
    string input, sudoku[100];
    int count = 0;
    // read the file until 0
    getline(cin, input);
    while(input != "0") {
        sudoku[count++] = input;
        getline(cin, input);
    }

    // calculate the size of the sudoku
    int matrixSize = (sudoku[0].length()+1)/2, width = sudoku[0].length();
    // initialize a output matrix
    string output[100], temp[100];
    for(int i=0; i<matrixSize; i++) {
        output[i] = sudoku[i];
        temp[i] = sudoku[i];
    }
    for(int i=matrixSize; i<count; i++) {
        // change numbers
        if(sudoku[i][0] == '1') {
            char num1 = sudoku[i][2], num2 = sudoku[i][4];
            for(int row=0; row<matrixSize; row++) {
                for(int col=0; col<width; col+=2) {
                    if(output[row][col] == num1) output[row][col] = num2;
                    else if(output[row][col] == num2) output[row][col] = num1;
                }
            }
        }
        // change two big rows
        else if(sudoku[i][0] == '2') {
            char row1 = sudoku[i][2], row2 = sudoku[i][4];
            int irow1, irow2;
            if(row1 == '1') irow1 = 3;
            else if(row1 == '2') irow1 = 6;
            else irow1 = 0;
            if(row2 == '1') irow2 = 3;
            else if(row2 == '2') irow2 = 6;
            else irow2 = 0;
            string temp;
            for(int i=0; i<3; i++) {
                temp = output[irow1+i];
                output[irow1+i] = output[irow2+i];
                output[irow2+i] = temp;
            }
        }
        // change two big columns
        else if(sudoku[i][0] == '3') {
            char col1 = sudoku[i][2], col2 = sudoku[i][4];
            int icol1, icol2;
            if(col1 == '1') icol1 = 6;
            else if(col1 == '2') icol1 = 12;
            else icol1 = 0;
            if(col2 == '1') icol2 = 6;
            else if(col2 == '2') icol2 = 12;
            else icol2 = 0;
            char temp;
            for(int j=0; j<matrixSize; j++) { // the row num
                for(int i=0; i<6; i+=2) { // the column num
                    temp = output[j][icol2+i];
                    output[j][icol2+i] = output[j][icol1+i];
                    output[j][icol1+i] = temp;
                }
            }
        }
        // rotate for several times
        else if(sudoku[i][0] == '4') {
            int time = (int)sudoku[i][2] - 48;
            for(int k=0; k<time; k++) {
                cout << k << endl;
                for(int row=0; row<matrixSize; row++) {
                    for(int col=0; col<width; col+=2) {
                        output[col/2][(8-row)*2] = temp[row][col];
                    }
                }
                for(int row=0; row<matrixSize; row++) {
                    temp[row] = output[row];
                }
            }
        }
        // up-down or left-right flip
        else if(sudoku[i][0] == '5') {
            int flipKind = (int)sudoku[i][2] - 48;
            // up-down flip
            if(flipKind == 0) {
                for(int row=0; row<matrixSize; row++) {
                    output[row] = temp[8-row];
                }
            }
            // left-right flip
            else {
                for(int row=0; row<matrixSize; row++) {
                    for(int col=0; col<width; col++) {
                        output[row][col] = temp[row][16 - col];
                    }
                }
            }
        }
    }


    // show output matrix
    for(int i=0; i<matrixSize; i++) {
        cout << output[i] << endl;
    }
    return 0;
}
