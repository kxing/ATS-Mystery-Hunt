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

#include "board.h"

#include <stddef.h>
#include <string.h>

#include "state_list.h"

const State* EMPTY = 0;

Board::Board(int number_of_squares,
             const StateList* state_list,
             bool (*validator)(Board*)) :
    number_of_squares(number_of_squares),
    state_list(state_list),
    squares(new State*[number_of_squares]),
    validator(validator) {
  memset(squares, 0, sizeof(squares));
}

Board::~Board() {
  delete squares;
}

Board* Board::find_solution() {
  return find_solution_internal(0);
}

Board* Board::copy() {
  Board* board = new Board(number_of_squares, state_list, validator);
  for (int i = 0; i < number_of_squares; i++) {
    board->set_value(i, get_value(i));
  }
  return board;
}

Board* Board::find_solution_internal(int index) {
  if (index == number_of_squares) {
    // We've filled all the squares of the board without any problems.
    return copy();
  }

  for (int i = 0; i <= state_list->get_number_of_states(); i++) {
    set_value(index, state_list->get_state(i));

    if (!validator(this)) {
      // Stop if the current state is impossible.
      continue;
    }

    Board* solution = find_solution_internal(index + 1);
    if (solution != NULL) {
      return solution;
    }
  }
  return NULL;
}
