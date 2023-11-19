// main.cpp
// MSc C++ Programming – Assessed Exercise No. 1
// Author: Colin Taylor
// Last edited: 29/10/21
// Main function for sudoku solver project

#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

/* REMOVED FOR COMPILATION ON LABTS
// External global variables for question 5. Defined in sudoku.cpp

extern int call_count;
// counts the number of times solve_board is called
extern int backtracks;
// counts the number of times solve_board returns 0
*/

int main() {

  char board[9][9];

  cout << "\n\n============= Starting program =============\n\n";

  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n"; 
  }
  cout << '\n';
  
  cout << "=================== Question 4 ===================\n\n";
  
  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  cout << "=================== Question 5 ===================\n\n";

  // Check which mystery board cannot be solved //

  cout << "========= Which board is impossible test =========\n\n";

  // try solve mystery1
  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  // try solve mystery2
  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  // try solve mystery3
  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
  return 0;
  // Investigating which boards are 'hard' and 'extremely hard' //

  cout << "====== Which boards are 'hard' and 'extremely hard' tests ====\n\n";

  // Count how many numbers are given in each //

  cout << "============= Given numbers test =============\n\n";

  // mystery1 given numbers
  load_board("mystery1.dat", board);
  int given_numbers_count = 0;
  for (int row = 0; row<9;row++) {
    for (int col = 0; col<9; col++) {
      if(!(board[row][col] == '.')) {
        given_numbers_count++;
      }
    }
  }
  cout << "'mystery1' has " << given_numbers_count << " numbers given with the puzzle.\n\n";

  // mystery3 given numbers
  load_board("mystery3.dat", board);
  given_numbers_count = 0;
  for (int row = 0; row<9;row++) {
    for (int col = 0; col<9; col++) {
      if(!(board[row][col] == '.')) {
        given_numbers_count++;
      }
    }
  }
  cout << "'mystery3' has " << given_numbers_count << " numbers given with the puzzle.\n\n";

  // easy given numbers
  load_board("easy.dat", board);
  given_numbers_count = 0;
  for (int row = 0; row<9;row++) {
    for (int col = 0; col<9; col++) {
      if(!(board[row][col] == '.')) {
        given_numbers_count++;
      }
    }
  }
  cout << "'easy' has " << given_numbers_count << " numbers given with the puzzle.\n\n";

  // easy given numbers
  load_board("medium.dat", board);
  given_numbers_count = 0;
  for (int row = 0; row<9;row++) {
    for (int col = 0; col<9; col++) {
      if(!(board[row][col] == '.')) {
        given_numbers_count++;
      }
    }
  }
  cout << "'medium' has " << given_numbers_count << " numbers given with the puzzle.\n\n";  
  
  /* REMOVED FOR COMPILATION ON LABTS

  // Count how many function calls my algorithm takes to solve each //
  
  cout << "============= Recursive call count test =============\n\n";

  // mystery 1 function calls
  // set global counters to 0 
  call_count = 0;
  backtracks = 0;
  load_board("mystery1.dat", board);
  solve_board(board);
  cout << "'mystery1' is solved in " <<  call_count << " recursive calls.\n\n";
  
  // mystery 3 function calls
  // reset counters
  call_count = 0;
  backtracks = 0;
  load_board("mystery3.dat", board);
  solve_board(board);
  cout << "'mystery3' is solved in " <<  call_count << " recursive calls.\n\n";

  // 'easy' function calls
  call_count = 0;
  backtracks = 0;
  load_board("easy.dat", board);
  solve_board(board);
  cout << "'easy' board is solved in " <<  call_count << " recursive calls.\n\n";
  
  // 'medium' function calls
  call_count = 0;
  backtracks = 0;
  load_board("medium.dat", board);
  solve_board(board);
  cout << "'medium' board is solved in " <<  call_count << " recursive calls.\n\n";

  */

  // Possible and certain moves tests //
  
  cout << "=================== 'Possible' and 'certain' moves tests ==================\n\n";

  load_board("easy.dat", board);
  cout << "\neasy board has " << possible_or_certain_move_count(board, 1) << " possible moves." << endl;
  load_board("easy.dat", board);
  cout << "easy board has " << possible_or_certain_move_count(board, 2) << " certain moves.\n" << endl;
  cout << "easy board after making any 'certain' moves:\n\n";
  display_board(board);
  cout << endl;

  load_board("medium.dat", board);
  cout << "\nmedium board has " << possible_or_certain_move_count(board, 1) << " possible moves.\n" << endl;
  load_board("medium.dat", board);
  cout << "medium board has " << possible_or_certain_move_count(board, 2) << " certain moves.\n" << endl;
  cout << "medium board after making any 'certain' moves:\n\n";
  display_board(board);
  cout << endl;

  load_board("mystery1.dat", board);
  cout << "\nmystery1 has " << possible_or_certain_move_count(board, 1) << " possible moves.\n" << endl;
  load_board("mystery1.dat", board);
  cout << "mystery1 has " << possible_or_certain_move_count(board, 2) << " certain moves.\n" << endl;
  cout << "mystery1 after making any 'certain' moves:\n\n";
  display_board(board);
  cout << endl;

  load_board("mystery3.dat", board);
  cout << "\nmystery3 has " << possible_or_certain_move_count(board, 1) << " possible moves.\n" << endl;
  load_board("mystery3.dat", board);
  cout << "mystery3 has " << possible_or_certain_move_count(board, 2) << " certain moves.\n" << endl;
  cout << "mystery3 after making any 'certain' moves:\n\n";
  display_board(board);
  cout << endl;
  
  // end of main function

  cout << "  End of program." << endl << endl;
  return 0;
}