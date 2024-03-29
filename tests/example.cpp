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
// The following code solves the following problem:
//
// We have five people in a line, and each person is wearing a hat.
// Each hat is either red, white, or blue.
// Furthermore, we know that:
//  - Any two people sitting next to each other wear different-colored hats.
//  - The second person wears a blue hat.
//  - The hats belonging to the first and fourth people are the same color.
//  - Among the five hats, there is more than one blue hat.
//  - The hat belonging to the fourth person is not white.
//
// The only solution is: Red, Blue, White, Red, Blue.
// -----------------------------------------------------------------------------

#include <stdio.h>

#include "include/brute_force_solver/board.h"
#include "include/brute_force_solver/state.h"
#include "include/brute_force_solver/state_list.h"

#include "include/stopwatch/stopwatch.h"

using lib_kxing::brute_force_solver::Board;
using lib_kxing::brute_force_solver::State;
using lib_kxing::brute_force_solver::StateList;

using lib_kxing::stopwatch::StopWatch;

const int NUMBER_OF_SQUARES = 5;
const int NUMBER_OF_STATES = 3;

const State RED_STATE("Red");
const State BLUE_STATE("Blue");
const State WHITE_STATE("White");

const State* RED = &RED_STATE;
const State* BLUE = &BLUE_STATE;
const State* WHITE = &WHITE_STATE;

const State* STATES[NUMBER_OF_STATES] = {
  RED,
  BLUE,
  WHITE,
};

const StateList STATE_LIST(STATES, NUMBER_OF_STATES);

bool validator(const Board* const board) {
  // Any two people sitting next to each other wear different-colored hats.
  for (int i = 1; i < NUMBER_OF_SQUARES; i++) {
    if (board->is_empty(i - 1) || board->is_empty(i)) {
      continue;
    }
    if (board->get_value(i - 1) == board->get_value(i)) {
      return false;
    }
  }

  // The second person wears a blue hat.
  if (!board->is_empty(2 - 1) && board->get_value(2 - 1) != BLUE) {
    return false;
  }

  // The hats belonging to the first and fourth people are the same color.
  if (!board->is_empty(1 - 1) && !board->is_empty(4 - 1) &&
      board->get_value(1 - 1) != board->get_value(4 - 1)) {
    return false;
  }

  // Among the five hats, there is more than one blue hat.
  int blue_hat_counter = 0;
  for (int i = 0; i < NUMBER_OF_SQUARES; i++) {
    if (board->is_empty(i) || board->get_value(i) == BLUE) {
      blue_hat_counter++;
    }
  }
  if (blue_hat_counter <= 1) {
    return false;
  }

  // The hat belonging to the fourth person is not white.
  if (board->get_value(4 - 1) == WHITE) {
    return false;
  }

  return true;
}

void solve() {
  int search_order[NUMBER_OF_SQUARES] = {2 - 1, 1 - 1, 4 - 1, 3 - 1, 5 - 1};

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
}

int main() {
  StopWatch::time_function(&solve);
  return 0;
}
