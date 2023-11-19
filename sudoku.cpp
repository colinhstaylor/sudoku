// sudoku.cpp
// MSc C++ Programming – Assessed Exercise No. 1
// Author: Colin Taylor
// Last edited: 29/10/21
// Function definitions for the sudoku solver project

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* REMOVED FOR COMPILATION ON LABTS
// extern global variable initialisations for question 5
int call_count = 0;
int backtracks = 0;
*/

/* You are pre-supplied with the functions below. Add your own
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) { 
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

// Functions for question 1 //
//** need to make board inputs defensive
bool is_complete(char board[9][9]) {
// returns 0 if any '.' are on the board else returns 1
  for (int rows=0;rows<9;rows++) {
    for (int cols=0;cols<9;cols++){
      if (board[rows][cols] == '.')
        return 0;
    }
  }
	return 1;
}

// Functions for question 2 //

bool test_position(const char board[SIZE_OF_BOARD][9]) {
  cout << "Trying to put digit 1 into every available square.\n\n";
  char position[] = {'A','1'};
  for (char row = 'A'; row <= 'H'; row++) {
    for (char col= '1'; col<= '9'; col++) {
      position[0] = row;
      position[1] = col;
      if(test_move(position, '1', board)) {
        cout << "1 can be entered into " << position << '\n';
      }
    }
  }
  cout << "Position check complete. Compare with comments in main.cpp\n\n";
}

bool test_digits(const char board[SIZE_OF_BOARD][SIZE_OF_BOARD]) {
  cout << "\nTrying all digits 1-9 into B8.\n\n";
  for (char digit = 49; digit <= 57; digit++) {
    if(test_move("B8", digit, board)) cout << digit << " can be entered here.\n";
  }
  cout << "Digit check complete. Compare with comments in main.cpp\n\n";
}

bool test_move(const char* position, char digit, const char board[9][9]) {

  // VALID PARAMETER CHECKS //

  // check digit is valid
  if (digit < '1' || digit > '9') {
    //cout << "Digit is out of range." << endl;
    return 0;
  }

  // convert row and column characters (e.g. "A1") in position string
    // to ints (1-9)
  int row = position[0] - 64, col = position[1] - 48;

  // check position is valid
  if (row < 1 || row > 9 || col < 1 || col > 9) {
    //cout << "Position is out of range.\n";
    return 0;
  }
 
  // CHECK IF POSITION IS ALREADY FILLED //

  // check if square is taken

  if(board[row-1][col-1] != '.') { 
    //cout << "There is already a digit here" << endl;
    return 0;
  }
  // SUDOKU MOVE RULE CHECKS //

  // check if the digit is already in the row
  for (int n = 0; n<9; n++) {
    // disregards any entry into the position being considered
    if (n == col -1)
      continue;
    // then check the digit is not elsewhere in the row
    if (board[row-1][n] == digit) {
      //cout << "Digit is already in the row" << endl;
      return 0;
    }
  }
 
  // check if the digit is already in the column
  for (int n = 0; n<9; n++) {
    if (n == row -1)
      continue;
    if (board[n][col-1] == digit) {
      //cout << "Digit is already in column." << endl;
      return 0;
    }
  }
  
  // check if the digit is in the same 3x3 box as position
  // uses modulo to ensure the loop starts from the top left square of the
  // 3x3 box the square is contained in
  int startrow = row - ((row-1) % 3); 
  int startcol = col - ((col-1) % 3); 
  for (int n = startrow; n<startrow+3; n++) {
    for (int m = startcol; m<startcol+3; m++) {
      if(board[n-1][m-1]==digit) {
        //cout << "Digit is already in box.\n";
        return 0;
      }
    }
  }

  // return 1 if no test conditions are true
  return 1;
}

bool make_move(const char* position, char digit, char board[9][9]) {
  if(test_move(position, digit, board)) {
    int row = position[0] - 64, col = position[1] - 48;
    board[row-1][col-1] = digit;
    return 1;
  }
  return 0;
}

// Functions for question 3 //

bool save_board(const char* filename, char board[9][9]) {

  cout << "Saving Sudoku board to file '" << filename << "'... ";

  ofstream out(filename);
  // check that outstream has been created successfully
  if (!out) {
    cout << "Failed to create output stream!\n";
  }
  assert(out);

  int row = 0;
  for (row = 0; row<9; row++) {
    for (int col=0; col<9; col++) {
      // check the character being sent to output is valid before sending
      assert(board[row][col] == '.' || isdigit(board[row][col]));
      // send the character to the output file
      out << board[row][col];
    }
    out << endl;
  }
  
  // check the output stream has not been corrupted
  cout << ((out) ? "Success!" : "Failed!") << '\n';
  assert(out);
	if (out) return 1;
  else return 0;
}

// Functions for question 4 //

bool solve_board(char board[9][9]) {
  // global variable counter for question 5
  // call_count++; REMOVED FOR COMPILATION ON LABTS
  // iterate over the board from A1 through to I9
  for (int row = 0; row<9;row++) {
    for (int col = 0; col<9; col++) {
      // when reached an empty square
      if (board[row][col] == '.') {
        // loop through all the digits 1-9
        for (char digit = '1'; digit <= '9'; digit++) {
          char position[2] = {static_cast<char>(row+65),static_cast<char>(col+49)};
          // check if digit can be entered in this empty square
          if(make_move(position, digit, board)) {
            // if it can, then try to solve the board with this digit added
            if(solve_board(board)) {
              // if the board is solved, return 1
              return 1;
            }
            // otherwise, undo the move and continue trying digits
            else {board[row][col] = '.';}
          }
        }
        // global variable for question 5
        // backtracks++; REMOVED FOR COMPILATION ON LABTS
        // if no digit fits in the empty square, return 0 and return to line 232 in the previous stack-frame/function call
        return 0;
      }
    }
  }
  // if no empty squares are found on a call of solve_board
  // check it is complete and valid with is_complete (this should always pass)
  if(is_complete(board)) {
    return 1;
  }
  // back-stop return 0 in-case anything unexpected happens 
  return 0;
}

// **ALTERNATIVE METHOD FOR SOLVE BOARD
/*
char const move_row(char const row, char const col) {
  if(col == '9') {
      return row+1;
    }
  else return row;
}

char const move_col(char col) {
  if(col == '9') {
      return "1";
    }
  else return col+1;
}

// helper function to solve rest of board from a starting position
bool solve_rest_of_board(char const row, char const col, char board[9][9]) {
  // check if board complete before continuing
  if(is_complete(board)) {
    return 1;
  }
  // check we are at a empty square
  if (board[row-65][col-49] != '.') {
    //cout << "this square is taken\n";
    solve_rest_of_board(move_row(row,col),move_col(row),board);
  }

  // try all the digits at position
  for (char digit = '1'; digit <= '9'; digit++) {
    // if can enter current digit at current position
    // do and move on through the board to the next square
    char* position = {row,col};
    if(make_move(position, digit, board)) {
        if(solve_rest_of_board(move_row(row,col),move_col(col), board)) {
          return 1;
        }
        else {
          //undo the move made at this position
          board[row-65][col-49] = '.';
        }
    }
  }
  // if no digit can be put here we need to go back
  return 0;
}

// solve the board assuming no wrong moves have been made/blank board //
bool solve_board(char board[9][9]) {
  // start at the top
  char position[] = "A1"; //**just put straight into function?
  if(solve_rest_of_board("A","1", board))
    return 1;
  display_board(board);
  return 0;
}
*/

// Functions for question 5 //

int possible_or_certain_move_count(char board[9][9], int const returnvalue) {
  // counter for possible moves in all passes
  int overallpossmoves = 0;
  // counter for certain moves in all passes
  int overallcertainmoves = 0;

  // counter for possible moves in each pass
  int onepasspossmoves = 1;
  // while loop ends when a full pass is made and no certain moves found
  while(onepasspossmoves) {
    // reset onepass counter each pass
    onepasspossmoves = 0;
    // loop over entire board
    for (int rows=0;rows<9;rows++) {
      for (int cols=0;cols<9;cols++) {
        char position[] ={char(rows+65), char(cols+49)};
        // when an empty square is reached
        if (board[rows][cols] == '.') { 
          // count how many moves are possible at this position
          int possmovecount = 0;
          for(char digit = 49; digit <= 57; digit++) {
            if(test_move(position, digit, board)) {
              possmovecount++;
              overallpossmoves++;
            }
          }
          // if only one move is possible, then it is a 'certain' move
          if(possmovecount == 1) {
            // loop over digits to find the move again
            for(char digit = 49; digit<=57; digit++) {
                      // make the move
                      make_move(position, digit, board);
                      // count that one (more) move was made this pass
                      onepasspossmoves++;
                      overallcertainmoves++;
            }
          }
        }
      }
    }
    // loop exits if a full pass results in no moves made
  }

  // 1 returns total possible moves recorded throughout the function call
  if(returnvalue == 1) {
    return overallpossmoves;
  }
  // 2 returns the certain moves made throughout the function call
  if(returnvalue == 2) {
    return overallcertainmoves;
  }
  // return value back-stop in case anything goes wrong
  else return 0;
}