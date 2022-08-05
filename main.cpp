//
//  main.cpp
//  Homework4
//
//  Created by Travis Cassell on 7/22/22.
//

#include <iostream>
#include <thread>
#include <cstdlib>

using namespace std;
// CHANGE NUMBERS TO TEST VALIDITY OF BOARD
int sudoku_board[9][9] = {{6,2,4,5,3,9,1,8,7},
                          {5,1,9,7,2,8,6,3,4},
                          {8,3,7,6,1,4,2,9,5},
                          {1,4,3,8,6,5,7,2,9},
                          {9,5,8,2,4,7,3,6,1},
                          {7,6,2,3,9,1,4,5,8},
                          {3,7,1,9,5,6,8,4,2},
                          {4,9,6,1,8,2,5,7,3},
                          {2,8,5,4,7,3,9,1,6}};

// VALID SUDOKU BOARD EXAMPLE
/*
{{6,2,4,5,3,9,1,8,7},
{5,1,9,7,2,8,6,3,4},
{8,3,7,6,1,4,2,9,5},
{1,4,3,8,6,5,7,2,9},
{9,5,8,2,4,7,3,6,1},
{7,6,2,3,9,1,4,5,8},
{3,7,1,9,5,6,8,4,2},
{4,9,6,1,8,2,5,7,3},
{2,8,5,4,7,3,9,1,6}};
 */

int thread_check[27]; // Array to hold results of thread tests

void check_row(int); // Function to validate the rows
void check_column(int); // Function to validate the columns
void check_subgrid(int, int, int grid_num); // Function to validate subgrids

int main(int argc, const char * argv[]) {
    
    cout << "testing sudoku board... \n";
    
    // THREADS TO CHECK ROWS
    thread t1 (check_row, 0);
    thread t2 (check_row, 1);
    thread t3 (check_row, 2);
    thread t4 (check_row, 3);
    thread t5 (check_row, 4);
    thread t6 (check_row, 5);
    thread t7 (check_row, 6);
    thread t8 (check_row, 7);
    thread t9 (check_row, 8);
    
    // THREADS TO CHECK COLUMNS
    thread t10 (check_column, 0);
    thread t11 (check_column, 1);
    thread t12 (check_column, 2);
    thread t13 (check_column, 3);
    thread t14 (check_column, 4);
    thread t15 (check_column, 5);
    thread t16 (check_column, 6);
    thread t17 (check_column, 7);
    thread t18 (check_column, 8);
    
    // THREADS TO CHECK SUBGRIDS
    thread t19 (check_subgrid, 0, 0, 19);
    thread t20 (check_subgrid, 0, 3, 20);
    thread t21 (check_subgrid, 0, 6, 21);
    thread t22 (check_subgrid, 3, 0, 22);
    thread t23 (check_subgrid, 3, 3, 23);
    thread t24 (check_subgrid, 3, 6, 24);
    thread t25 (check_subgrid, 6, 0, 25);
    thread t26 (check_subgrid, 6, 3, 26);
    thread t27 (check_subgrid, 6, 6, 27);
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();
    t11.join();
    t12.join();
    t13.join();
    t14.join();
    t15.join();
    t16.join();
    t17.join();
    t18.join();
    t19.join();
    t20.join();
    t21.join();
    t22.join();
    t23.join();
    t24.join();
    t25.join();
    t26.join();
    t27.join();

    // Check test array to verify whether board is valid sudoku
    for(int x = 0; x < 27; x++) {
        if(thread_check[x] == 0) {
            cout << "Not a valid sudoku board \n";
            return 0;
        }
    }
    cout << "Sudoku board is valid \n";
    
    return 0;
}
// FUNCTION TO VERIFY VALID ROW
void check_row(int row) {
    int check[9]; // Array to check if all 9 are valid
    int check_array[9] = {1,2,3,4,5,6,7,8,9}; // Array to hold possible values 1 - 9

    for(int x = 0; x < 9; x++) {
        for(int y = 0; y < 9; y++) {
            if(sudoku_board[row][x] == check_array[y]) {
                check[x] = 1; // If index valid, set as 1
                check_array[y] = -1; // Remove value from check array to not re-use
            }
        }
    }
    for(int x = 0; x < 9; x++) {
        if(check[x] == 0) {
            thread_check[row] = 0; // If not found, row not valid
            return;
        }
    }
    thread_check[row] = 1; // Current index row valid
}
// FUNCTION TO VERIFY VALID COLUMN
// Same concept as check_row
void check_column(int column) {
    int check[9];
    int check_array[9] = {1,2,3,4,5,6,7,8,9};
    
    for(int x = 0; x < 9; x++) {
        for(int y = 0; y < 9; y++) {
            if(sudoku_board[x][column] == check_array[y]) {
                check[x] = 1;
                check_array[y] = -1;
            }
        }
    }
    for(int x = 0; x < 9; x++) {
        if(check[x] == 0) {
            thread_check[column + 9] = 0;
            return;
        }
    }
    thread_check[column + 9] = 1;
}
// FUNCTION TO VERIFY VALID SUBGRID
// Same concept as check_row and check_column
// But must check sub grid of 3 x 3
void check_subgrid(int start_row, int start_column, int grid_num) {
    int check[9];
    int temp = start_column;
    int check_array[9] = {1,2,3,4,5,6,7,8,9};
    
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            for(int z = 0; z < 9; z++) {
                if(sudoku_board[start_row][temp] == check_array[z]) {
                    check[x] = 1;
                    check_array[z] = -1;
                }
            }
            temp++;
        }
        start_row++;
        temp = start_column;
    }
    for(int x = 0; x < 9; x++) {
        if(check[x] == 0) {
            thread_check[grid_num - 1] = 0;
            return;
        }
    }
    thread_check[grid_num - 1] = 1;
}

// All possible subgrids
// subgrid 1: (0,0) x (2,2)
// subgrid 2: (0,3) x (2,5)
// subgrid 3: (0,6) x (2,8)
// subgrid 4: (3,0) x (5,2)
// subgrid 5: (3,3) x (5,5)
// subgrid 6: (3,6) x (5,8)
// subgrid 7: (6,0) x (8,2)
// subgrid 8: (6,3) x (8,5)
// subgrid 9: (6,6) x (8,8)
