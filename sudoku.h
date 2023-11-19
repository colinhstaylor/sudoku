// sudoku.h
// MSc C++ Programming – Assessed Exercise No. 1
// Author: Colin Taylor
// Last edited: 29/10/21
// Header file for the sudoku solver project

#ifndef SUDOKU_H
#define SUDOKU_H

int const SIZE_OF_BOARD = 9;

// Pre-supplied helper functions //

void load_board(const char* filename, char board[9][9]);
// precondition : an empty [9][9] 2D char array and a dat file containing
    // an unsolved sudoku board
// postcondition: the array will be filled with the board data from file

void display_board(const char board[9][9]);
// precondition : char array containing a board
// postcondition: board is printed to output

// Functions for question 1 //

bool board_is_vaalid(char board[9][9]);
// precondition : board array
// postcondition: returns 0 if the board contains any invalid characters
    // returns 1 otherwise

bool is_complete(char board[9][9]);
// precondition : char array board
// postcondition: returns true if the board has a digit in each square
    // or false if there are any empty squares

// Functions for quesiton 2 //

bool test_position(const char board[SIZE_OF_BOARD][9]);

bool test_digits(const char board[SIZE_OF_BOARD][SIZE_OF_BOARD]);

bool test_move(const char* position, char digit, const char board[9][9]);
// checks if a given move is valid
// precondition : a position in the form "A1", a char digit "1"-"9"
    // and an unsolved board array
// postcondition: returns true if the digit can be placed on the board
    // in the position specified following the rules of sudoku
    // returns false if the move violates the rules or is out
    // of range 
// Note: ALLOWS moves on top of previous moves

bool make_move(const char* position, char digit, char board[9][9]);
// calls test_move then makes the move if valid
// precondition : a position in the form "A1", a char digit "1"-"9"
    // and an unsolved board array
// postcondition: the board with the position filled with digit if
    // test_move returns true
    // return values identical to test_move

// Functions for question 3 //

bool save_board(const char* filename, char board[9][9]);
// saves board to file
// precondition : a board array and a filename for output
// postcondition: a dat file with the board saved to it in the format 
    // load_board takes. digits on a row with . representing
    // empty squares and newline every line and at the end

// Functions for question 4 //

bool solve_board(char board[9][9]);
// attempts to solve a given board using recursive backtracking
// precondition : an unsolved board array
// postcondition: returns true if the board can be solved and the board 
    // array will then contain the solved board
    // returns false if the board cannot be solved

// Functions for question 5 //

int possible_or_certain_move_count(char board[9][9], int const returnvalue);
// checks the number of 'possible' or 'certain' moves on a given board
    // as selected by the returnvalue parameter
// precondition : an unsolved board array and a returnvalue of 1 or 2
// operation    : attempts to make any and all certain moves that can be
    // made. A certain move would be a case where only one digit can be
    // place in a given position
// postcondition: depends on returnvalue parameter:
    // for returnvalue = 1: returns the number of 'possible moves'
        // this is defined as the number of times a digit was found to be
        // a valid move at a position during the process of making certain
        // moves
    // for returnvalue = 2: returns the number of 'certain moves'
        // defined as the number of certain moves found. This simply
        // counts the number of moves made by this function
    // additionall postcondition: the board array input is always updated to 
        // reflect all the certain moves made by the function

#endif