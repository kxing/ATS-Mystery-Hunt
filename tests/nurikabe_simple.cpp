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
// The following code solves the example Nurikabe problem found at:
// http://puzzlepicnic.com/genre?islands
//
// We encode the squares as shown below:
//
//  0  1  2  3  4
//  5  6  7  8  9
// 10 11 12 13 14
// 15 16 17 18 19
// 20 21 22 23 24
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/board.h"
#include "include/state.h"
#include "include/state_list.h"

const int NUMBER_OF_ROWS = 5;
const int NUMBER_OF_COLUMNS = 5;
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

const int NUMBER_OF_DIRECTIONS = 4;
const int delta_x[NUMBER_OF_DIRECTIONS] = {1, 0, -1, 0};
const int delta_y[NUMBER_OF_DIRECTIONS] = {0, 1, 0, -1};

int row_of_square(int square) {
  return square / NUMBER_OF_COLUMNS;
}

int column_of_square(int square) {
  return square % NUMBER_OF_COLUMNS;
}

int row_and_column_to_square(int row, int column) {
  return row * NUMBER_OF_COLUMNS + column;
}

const int VARIABLE = NUMBER_OF_SQUARES + 1;

// Returns true if one of the following conditions is true:
//    - The size of the block of either land/water starting at |square| is
//      exactly |target|.
//    - The block of land/water starting at |square| touches an EMPTY square,
//      and the size of the block of land/water is not already larger than
//      |target|.
//
// If VARIABLE is passed in as the |target| parameter, the function will only
// return true in the latter case.
//
// The function marks all visited squares in the block of land/water in the
// |checked| array of size NUMBER_OF_SQUARES.
bool can_match_group_size(const Board* const board,
                          const State* const state_type,
                          int square,
                          int target,
                          bool* checked) {
  // Accept if the square is empty.
  if (board->get_value(square) == EMPTY) {
    return true;
  }

  // Reject if the square is of the wrong type.
  if (board->get_value(square) != state_type) {
    return false;
  }

  // We use BFS for flood-fill.
  int queue[NUMBER_OF_SQUARES];
  int length_of_queue = 0;
  int processed = 0;

  // Add the original square to the queue.
  queue[length_of_queue++] = square;
  checked[square] = true;

  // Whether we have hit an EMPTY square.
  bool tentative_accept = false;
  while (processed < length_of_queue) {
    // Go through all four adjacent squares.
    for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++) {
      int next_row = row_of_square(queue[processed]) + delta_x[i];
      int next_column = column_of_square(queue[processed]) + delta_y[i];

      // Ignore this square if we fall off the board.
      if (!(0 <= next_row && next_row < NUMBER_OF_ROWS &&
            0 <= next_column && next_column < NUMBER_OF_COLUMNS)) {
        continue;
      }

      // Process this square.
      int next_square = row_and_column_to_square(next_row, next_column);

      if (board->get_value(next_square) == state_type) {
        if (checked[next_square]) {
          // We've already processed this.
          continue;
        }
        queue[length_of_queue++] = next_square;
        checked[next_square] = true;
        if (length_of_queue > target) {
          return false;
        }
      } else if (board->get_value(next_square) == EMPTY) {
        tentative_accept = true;
      }
    }
    processed++;
  }
  if (tentative_accept) {
    return true;
  }

  return (length_of_queue == target);
}

bool validator(const Board* const board) {
  bool checked[NUMBER_OF_SQUARES];
  memset(checked, 0, sizeof(checked));

  // The number 2 in the first row, second column.
  if (!can_match_group_size(board,
                            FILLED,
                            row_and_column_to_square(0, 1),
                            2,
                            checked)) {
    return false;
  }
  // The number 2 in the first row, fifth column.
  if (!can_match_group_size(board,
                            FILLED,
                            row_and_column_to_square(0, 4),
                            2,
                            checked)) {
    return false;
  }
  // The number 3 in the third row, fourth column.
  if (!can_match_group_size(board,
                            FILLED,
                            row_and_column_to_square(2, 3),
                            3,
                            checked)) {
    return false;
  }
  // The number 2 in the fourth row, third column.
  if (!can_match_group_size(board,
                            FILLED,
                            row_and_column_to_square(3, 2),
                            2,
                            checked)) {
    return false;
  }

  // Check that there aren't any uncounted islands.
  for (int i = 0; i < NUMBER_OF_SQUARES; i++) {
    if (board->get_value(i) == FILLED && !checked[i] &&
        !can_match_group_size(board, FILLED, i, VARIABLE, checked)) {
      return false;
    }
  }

  // The no-lakes rule.
  for (int i = 1; i < NUMBER_OF_ROWS; i++) {
    for (int j = 1; j < NUMBER_OF_COLUMNS; j++) {
      if (board->get_value(row_and_column_to_square(i, j)) == UNFILLED &&
          board->get_value(row_and_column_to_square(i - 1, j)) == UNFILLED &&
          board->get_value(row_and_column_to_square(i, j - 1)) == UNFILLED &&
          board->get_value(row_and_column_to_square(i - 1, j - 1)) ==
              UNFILLED) {
        return false;
      }
    }
  }

  // The contiguous stream rule.
  for (int i = 0; i < NUMBER_OF_SQUARES; i++) {
    if (board->get_value(i) == UNFILLED && !checked[i] &&
        !can_match_group_size(board,
                              UNFILLED,
                              i,
                              NUMBER_OF_SQUARES - 9,
                              checked)) {
      return false;
    }
  }
  return true;
}

int main() {
  int search_order[NUMBER_OF_SQUARES] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24,
  };

  Board board(NUMBER_OF_SQUARES, &STATE_LIST, search_order, &validator);
  Board* solution = board.find_solution();

  if (solution == NULL) {
    // Found no solution.
    printf("No solution found\n");
  } else {
    // Found a solution - print it out, four to a line.
    solution->pretty_print(NUMBER_OF_COLUMNS);
    delete solution;
  }
  return 0;
}
