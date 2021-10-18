#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

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

/* Boolean function is_complete(board) which takes a 9 ×9 array of characters representing a Sudoku board 
and returns true if all board positions are occupied by digits, and false otherwise. */
bool is_complete(const char board[9][9])
{
  for (int row=0; row<9; row++) {
    for (int col=0; col<9; col++) {
      if (!isdigit(board[row][col])) return false;
    }
  }
  return true;
}

/* Boolean function make move(position, digit, board) which attempts to place a digit onto a Sudoku board at a given position. 
Here position is a two-character string denoting row (A to I) and column (1 to 9) board coordinates (e.g. “I8” ), 
digit is a character denoting the digit to be placed (from ’1’ to ’9’), 
and board is a two-dimensional character array. 

If position is invalid (e.g. because the coordinates are out of range), 
or the placing of the digit at position is invalid (e.g. because it would result in two copies of the same digit in the same row), 
then the return value of the function should be false, and board should be unaltered. 
Otherwise, the return value of the function should be true and board should be updated to
reflect the placing of digit at position.*/
bool make_move(const char move[2], const char digit, char board[9][9])
{
  int row_index = (move[0]-65), col_index = (move[1]-49);

  // Invalid position
  if (move[0] < 65 || move[0] > 73 || move[1] < 49 || move[1] > 57) return false;

  // Invalid digit
  if (digit < 49 || digit > 57) return false;

  // Invalid move as there is the same digit in the same row
  for (int col=0; col<9; col++) {
    if (board[row_index][col] == digit) return false;
  }
  // Invalid move as there is the same digit in the same column
  for (int row=0; row<9; row++) {
    if (board[row][col_index] == digit) return false;
  }

  // Valid move: update board with digit and return true
  board[row_index][col_index] = digit;
  return true;
}

/* Boolean function save board(filename, board) which outputs the two-dimensional character array board 
to a file with name filename. The return value should be true if the file was successfully written, and
false otherwise. */
bool save_board(const char* filename, const char board[9][9])
{
  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ofstream out;
  ofstream test_out;
  out.open(filename);

  for (int row=0; row<9; row++) {
    for (int col=0; col<9; col++) {
      out << board[row][col];
    }
    out << endl;
  }

  out.close();

  /* NEED TO INSERT CODE HERE to check if output file has any failures */
  test_out.open(filename);
  if (test_out.fail()) return false;

  return true;
}