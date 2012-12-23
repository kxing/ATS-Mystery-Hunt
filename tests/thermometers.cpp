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
#include <stdlib.h>

#include "include/board.h"
#include "include/state.h"
#include "include/state_list.h"

const int NUMBER_OF_ROWS = 4;
const int NUMBER_OF_COLUMNS = 4;
const int NUMBER_OF_SQUARES = NUMBER_OF_ROWS * NUMBER_OF_COLUMNS;
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

// Checks to see if the number of filled squares in [start, end] (with step
// size |step| can ever equal |target|.
bool valid_line(const Board* const board,
                int start,
                int end,
                int step,
                int target) {
  int min_sum = 0;
  int max_sum = 0;
  for (int i = start; i <= end; i += step) {
    if (board->get_value(i) == FILLED) {
      min_sum++;
      max_sum++;
    } else if (board->get_value(i) == EMPTY) {
      max_sum++;
    }
  }
  if (min_sum > target || max_sum < target) {
    return false;
  }
  return true;
}

bool valid_thermometer(const Board* const board, int start, int end, int step) {
  assert(((end - start) % abs(step)) == 0);
  assert(((end - start) / step) >= 0);
  int bottom = start;
  int next = start + step;

  while (bottom != end) {
    if (board->get_value(bottom) == UNFILLED &&
        board->get_value(next) == FILLED) {
      return false;
    }
    bottom += step;
    next += step;
  }
  return true;
}

bool validator(const Board* const board) {
  // Thermometer along row 1.
  if (!valid_thermometer(board, 0, 3, 1)) {
    return false;
  }

  // Row 1 count.
  if (!valid_line(board, 0, 3, 1, 3)) {
    return false;
  }

  // Thermometer along row 2.
  if (!valid_thermometer(board, 7, 5, -1)) {
    return false;
  }

  // Row 2 count.
  if (!valid_line(board, 4, 7, 1, 2)) {
    return false;
  }

  // Thermometer along row 3.
  if (!valid_thermometer(board, 10, 9, -1)) {
    return false;
  }

  // Row 3 count.
  if (!valid_line(board, 8, 11, 1, 1)) {
    return false;
  }

  // Thermometer along row 4.
  if (!valid_thermometer(board, 14, 13, -1)) {
    return false;
  }

  // Row 4 count.
  if (!valid_line(board, 12, 15, 1, 3)) {
    return false;
  }

  // Thermometer along column 1.
  if (!valid_thermometer(board, 12, 4, -4)) {
    return false;
  }

  // Column 1 count.
  if (!valid_line(board, 0, 12, 4, 3)) {
    return false;
  }

  // Column 2 count.
  if (!valid_line(board, 1, 13, 4, 2)) {
    return false;
  }

  // Column 3 count.
  if (!valid_line(board, 2, 14, 4, 3)) {
    return false;
  }

  // Thermometer along column 4.
  if (!valid_thermometer(board, 11, 15, 4)) {
    return false;
  }

  // Column 4 count.
  if (!valid_line(board, 3, 15, 4, 1)) {
    return false;
  }

  return true;
}

int main() {
  int search_order[NUMBER_OF_SQUARES] = {
      0, 1, 2, 3, 12, 8, 4, 10, 9, 11, 15, 7, 6, 5, 14, 13,
  };

  Board board(NUMBER_OF_SQUARES, &STATE_LIST, search_order, &validator);
  Board* solution = board.find_solution();

  if (solution == NULL) {
    // Found no solution.
    printf("No solution found\n");
  } else {
    // Found a solution - print it out, four to a line.
    solution->pretty_print(4);
    delete solution;
  }
  return 0;
}
