// Header file "sudoku.h"

#ifndef SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]);
bool make_move(const char move[2], const char digit, char board[9][9]);
bool is_present_in_row(int row_index, const char digit, char board[9][9]);
bool is_present_in_column(int col_index, const char digit, char board[9][9]);
bool is_present_in_square(int row_index, int col_index, const char digit, char board[9][9]);
bool save_board(const char* filename, const char board[9][9]);
bool solve_board(char board[9][9]);
bool fill_empty_cells(int row, int col, char board[9][9]);
void determine_mystery_results(double mystery1, double mystery2, double mystery3);

#define SUDOKU_H
#endif