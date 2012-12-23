// Copyright (c) 2012 Kerry Xing
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

// -----------------------------------------------------------------------------
// The following code solves the example Thermometers problem found at:
// http://puzzlepicnic.com/genre?thermometers
//
// We encode the squares as shown below:
//
//  0  1  2  3
//  4  5  6  7
//  8  9 10 11
// 12 13 14 15
// -----------------------------------------------------------------------------

#include <stdio.h>

#include "board.h"
#include "state.h"
#include "state_list.h"

const int NUMBER_OF_SQUARES = 16;
const int NUMBER_OF_STATES = 2;

const State FILLED_STATE("F");
const State UNFILLED_STATE("U");

const State* FILLED = &FILLED_STATE;
const State* UNFILLED = &UNFILLED_STATE;

const State* STATES[NUMBER_OF_STATES] = {
  FILLED,
  UNFILLED,
};

const StateList STATE_LIST(STATES, NUMBER_OF_STATES);

// Rows use zero-based indexing.
bool valid_row_count(const Board* const board, int row, int target) {
  int min_sum = 0;
  int max_sum = 4;
  for (int i = 4 * row; i < 4 + 4 * row; i++) {
    if (board->get_value(i) == FILLED) {
      min_sum++;
    }
    if (board->get_value(i) == UNFILLED) {
      max_sum--;
    }
  }
  if (min_sum > target || max_sum < target) {
    return false;
  }
  return true;
}// Rows use zero-based indexing.

bool valid_column_count(const Board* const board, int column, int target) {
  int min_sum = 0;
  int max_sum = 4;
  for (int i = column; i < NUMBER_OF_SQUARES; i += 4) {
    if (board->get_value(i) == FILLED) {
      min_sum++;
    }
    if (board->get_value(i) == UNFILLED) {
      max_sum--;
    }
  }
  if (min_sum > target || max_sum < target) {
    return false;
  }
  return true;
}

bool validator(const Board* const board) {
  // Thermometer along row 1.
  if (board->get_value(0) == UNFILLED && board->get_value(1) == FILLED) {
    return false;
  }
  if (board->get_value(1) == UNFILLED && board->get_value(2) == FILLED) {
    return false;
  }
  if (board->get_value(2) == UNFILLED && board->get_value(3) == FILLED) {
    return false;
  }

  // Row 1 count.
  if (!valid_row_count(board, 0, 3)) {
    return false;
  }

  // Thermometer along row 2.
  if (board->get_value(7) == UNFILLED && board->get_value(6) == FILLED) {
    return false;
  }
  if (board->get_value(6) == UNFILLED && board->get_value(5) == FILLED) {
    return false;
  }

  // Row 2 count.
  if (!valid_row_count(board, 1, 2)) {
    return false;
  }

  // Thermometer along row 3.
  if (board->get_value(10) == UNFILLED && board->get_value(9) == FILLED) {
    return false;
  }

  // Row 3 count.
  if (!valid_row_count(board, 2, 1)) {
    return false;
  }

  // Thermometer along row 4.
  if (board->get_value(14) == UNFILLED && board->get_value(13) == FILLED) {
    return false;
  }

  // Row 4 count.
  if (!valid_row_count(board, 3, 3)) {
    return false;
  }

  // Thermometer along column 1.
  if (board->get_value(8) == UNFILLED && board->get_value(4) == FILLED) {
    return false;
  }
  if (board->get_value(12) == UNFILLED && board->get_value(8) == FILLED) {
    return false;
  }

  // Column 1 count.
  if (!valid_column_count(board, 0, 3)) {
    return false;
  }

  // Column 2 count.
  if (!valid_column_count(board, 1, 2)) {
    return false;
  }

  // Column 3 count.
  if (!valid_column_count(board, 2, 3)) {
    return false;
  }

  // Thermometer along column 4.
  if (board->get_value(11) == UNFILLED && board->get_value(15) == FILLED) {
    return false;
  }

  // Column 4 count.
  if (!valid_column_count(board, 3, 1)) {
    return false;
  }

  return true;
}

int main() {
  // TODO(kxing): Choose a better order.
  int search_order[NUMBER_OF_SQUARES] = {
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
  };

  Board board(NUMBER_OF_SQUARES, &STATE_LIST, search_order, &validator);
  Board* solution = board.find_solution();

  if (solution == NULL) {
    // Found no solution.
    printf("No solution found\n");
  } else {
    // Found a solution.
    solution->pretty_print();
    delete solution;
  }
  return 0;
}
