#include <iostream>
#include <cstdio>
#include <chrono>
#include "sudoku.h"

using namespace std;
using namespace std::chrono;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
	cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  // Include tests
  load_board("easy-insert-0.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // Invalid position
  cout << "Putting '1' into J8 is ";
  if (!make_move("J8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // Invalid digit (same digit in same row)
  cout << "Putting '1' into I9 is ";
  if (!make_move("I9", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // Invalid digit (same digit in same 3x3 square)
  cout << "Putting '3' into B8 is ";
  if (!make_move("B8", '3', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // Should be OK
  cout << "Putting '2' into C7 is ";
  if (!make_move("C7", '2', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
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

  // // write more tests

  // Test for failures
  load_board("easy-fail.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy-fail' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("medium-fail.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium-fail' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  cout << "=================== Question 5 ===================\n\n";

  // write more tests

  double mystery1_duration=0, mystery2_duration=0, mystery3_duration=0;

  load_board("mystery1.dat", board);
  auto begin1 = high_resolution_clock::now();
  if (solve_board(board)) {
    auto end1 = high_resolution_clock::now();
    mystery1_duration = duration_cast<microseconds>(end1 - begin1).count() /1000000.0;
    cout << "The 'mystery1' board has a solution:\n";
    cout << "The time taken was: " << mystery1_duration << "sec" << endl; 
    display_board(board);
  } else {
    cout << "A solution cannot be found for mystery1.\n";
  }
  cout << '\n';

  auto begin2 = high_resolution_clock::now();
  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    auto end2 = high_resolution_clock::now();
    mystery2_duration = duration_cast<microseconds>(end2 - begin2).count() /1000000.0;
    cout << "The 'mystery2 board has a solution:\n";
    cout << "The time taken was: " << mystery2_duration << "sec" << endl; 
    display_board(board);
  } else {
    cout << "A solution cannot be found for mystery2.\n";
  }
  cout << '\n';

  auto begin3 = high_resolution_clock::now();
  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    auto end3 = high_resolution_clock::now();
    mystery3_duration = duration_cast<microseconds>(end3 - begin3).count() /1000000.0;
    cout << "The 'mystery3' board has a solution:\n";
    cout << "The time taken was: " << mystery3_duration << "sec" << endl; 
    display_board(board);
  } else {
    cout << "A solution cannot be found for mystery3.\n";
  }
  cout << '\n';

  determine_mystery_results(mystery1_duration, mystery2_duration, mystery3_duration);

  return 0;
}
