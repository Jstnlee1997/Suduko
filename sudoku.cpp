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

/* Boolean function is_complete(board) which takes a 9×9 array of characters representing a Sudoku board 
and returns true if all board positions are occupied by digits, and false otherwise. */
bool is_complete(const char board[9][9])
{
  for (int row=0; row<9; row++) {
    for (int col=0; col<9; col++) {
      if (!isdigit(board[row][col]) || board[row][col] == '0') return false;
    }
  }
  return true;
}

/* Boolean function make_move(position, digit, board) which attempts to place a digit onto a Sudoku board at a given position. 
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

  // Invalid move as there is the same digit in the same row or column or 3x3 square
  if (is_present_in_row(row_index, digit, board) || is_present_in_column(col_index, digit, board) || is_present_in_square(row_index, col_index, digit, board)) return false;

  // Valid move: update board with digit and return true
  board[row_index][col_index] = digit;

  // Check if there is any ninth digit to fill in within the current row, column, OR 3x3 square
  fill_ninth_digit(row_index, col_index, board);

  return true;
}

/* Boolean function is_present_in_row to check if digit is present in the same row where the user wants to add a digit to. 
If digit is present: return true */
bool is_present_in_row(int row_index, const char digit, char board[9][9])
{
  for (int col=0; col<9; col++) {
    if (board[row_index][col] == digit) return true;
  }
  return false;
}

/* Boolean function is_present_in_column to check if digit is present in the same column where the user wants to add a digit to. 
If digit is present: return true */
bool is_present_in_column(int col_index, const char digit, char board[9][9])
{
  for (int row=0; row<9; row++) {
    if (board[row][col_index] == digit) return true;
  }
  return false;
}

/* Boolean function is_present_in_square to check if digit is present in the same 3x3 square where the user wants to add a digit to.
If digit is present: return true */
bool is_present_in_square(int row_index, int col_index, const char digit, char board[9][9])
{
  for (int row = (row_index-row_index%3); row < (row_index-row_index%3)+3; row ++) {
    for (int col = (col_index-col_index%3); col < (col_index-col_index%3)+3; col ++) {
      if (board[row][col] == digit) return true;
    }
  }
  return false;
}

/* Boolean function save_board(filename, board) which outputs the two-dimensional character array board 
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

/* Boolean function solve_board(board) which attempts to solve the Sudoku puzzle in input/output parameter board. 
The return value of the function should be true if a solution is found, in which case board should contain the solution found. 
In the case that a solution does not exist the return value should be false
and board should contain the original board */
bool solve_board(char board[9][9])
{
  /* Use recursive function fill_empty_cells to determine if there is a solution
  Start from first cell (0,0) */
  return fill_empty_cells(0, 0, board);
}

/* Boolean function fill_empty_cells which uses a recursive function to fill up each cell of the board recursively.
It begins from the top left most cell, and tries every digit (1-9) and fills up cells from left to right, then top to down.
If there are any conflicts, it would go back and resolve the conflicts.
If it returns false, the board would be untouched. */
bool fill_empty_cells(int row, int col, char board[9][9])
{
  // Translate current position to "move"
  char move[2];

  /* Start at first cell (going from left to right, then up to down) */
  while (row < 9 && isdigit(board[row][col]) && board[row][col] != '0') {
    col ++;
    if (col == 9) {
      row ++;
      col = 0;
    }
  }

  // Case: row == 9: Sudoku has been resolved
  if (is_complete(board)) return true;

  /* Case: reached a blank cell:
    - need to try digits from 1-9 */
  move[0] = row + 65;
  move[1] = col + 49; 
  for (char digit='1'; digit <= '9'; digit++) {
    if (make_move(move, digit, board) && fill_empty_cells(row, col, board)) return true;
  }

  /* Case: failure to resolve:
    - reset to empty character ' ' */
  board[row][col] = ' ';
  return false;
}

/* After adding a digit, Boolean function fill_ninth_digit will check 
if there is a row or column that has ended up with 8 numbers.
If yes it will automatically fill up the last empty space.

This function is to speed up performance.
 */
void fill_ninth_digit(int row_index, int col_index, char board[9][9])
{
  int empty_col, empty_row, empty_square;
  empty_col = empty_row = empty_square = -1;
  char move[2];

  // Check how many empty cells are there in current row
  for (int col=0; col<9; col++) {
    if (!isdigit(board[row_index][col]) || board[row_index][col] == '0') {
      if (empty_col != -1) {
        // More than 2 empty cells in current row -> reset
        empty_col = -1;
        break;
      }
      empty_col = col;
    }
  }
  // Fill up empty cell within current row with missing number
  if (empty_col != -1) {
    move[0] = row_index + 65;
    move[1] = empty_col + 49;
    for (char digit = '1'; digit <= '9'; digit++) {
      if (make_move(move, digit, board)) break;
    }
  }

  // Check how many empty cells are there in current column
  for (int row=0; row<9; row++) {
    if (!isdigit(board[row][col_index]) || board[row][col_index] == '0') {
      if (empty_row != -1) {
        // More than 2 empty cells in current column -> reset
        empty_row = -1;
        break;
      }
      empty_row = row;
    }
  }
  // Fill up empty cell within current column with missing number
  if (empty_row != -1) {
    move[0] = empty_row + 65;
    move[1] = col_index + 49;
    for (char digit = '1'; digit <= '9'; digit++) {
      if (make_move(move, digit, board)) break;
    }
  }

  // Check how many empty cells are there in current 3x3 square
  for (int row=(row_index-row_index%3); row<(row_index-row_index%3)+3; row++) {
    for (int col=(col_index-col_index%3); col<(col_index-col_index%3)+3; col++) {
      if (!isdigit(board[row][col]) || board[row][col] == '0') {
        if (empty_square != -1) {
          // More than 2 empty cells in current square -> reset
          empty_square = -1;
          break;
        }
        empty_col = col;
        empty_row = row;
      }
    }
  }
  // Fill up empty cell with missing number
  if (empty_square != -1) {
    move[0] = empty_row + 65;
    move[1] = empty_col + 49;
    for (char digit = '1'; digit <= '9'; digit++) {
      if (make_move(move, digit, board)) break;
    }
  }
}

/* Function to determine results of Mystery boards */
void determine_mystery_results(double mystery1, double mystery2, double mystery3)
{
  int result;

  // Mystery3 was impossible to solve
  if (mystery1 && mystery2) {
    if (mystery1 > mystery2) {
      result = mystery1/mystery2;
      cout << "Mystery2 was " << result << " times faster to solve than Mystery1!" << endl;
    } 
    else {
      result = mystery2/mystery1;
      cout << "Mystery1 was " << result << " times faster to solve than Mystery2!" << endl;
    }
  }

  // Mystery2 was impossible to solve
  if (mystery1 && mystery3) {
    if (mystery1 > mystery3) {
      result = mystery1/mystery3;
      cout << "Mystery3 was " << result << " times faster to solve than Mystery1!" << endl;
    } 
    else {
      result = mystery3/mystery1;
      cout << "Mystery1 was " << result << " times faster to solve than Mystery3!" << endl;
    }
  }

  // Mystery1 was impossible to solve
  if (mystery2 && mystery3) {
    if (mystery2 > mystery3) {
      result = mystery2/mystery3;
      cout << "Mystery3 was " << result << " times faster to solve than Mystery2!" << endl;
    } 
    else {
      result = mystery3/mystery2;
      cout << "Mystery2 was " << result << " times faster to solve than Mystery3!" << endl;
    }
  }
}