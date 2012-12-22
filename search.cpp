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

#include <stdio.h>

#include "board.h"
#include "state.h"
#include "state_list.h"

const int NUMBER_OF_SQUARES = 5;
const int NUMBER_OF_STATES = 5;

const State RED("red");
const State BLUE("blue");
const State YELLOW("yellow");
const State GREEN("green");
const State BLACK("black");

const State* STATES[5] = {
  &RED,
  &BLUE,
  &YELLOW,
  &GREEN,
  &BLACK,
};

const StateList STATE_LIST(STATES, NUMBER_OF_STATES);

bool validator(Board* b) {
  // Tests for distinct numbers.
  for (int i = 0; i < NUMBER_OF_SQUARES; i++) {
    if (b->get_value(i) == EMPTY) {
      continue;
    }

    for (int j = i + 1; j < NUMBER_OF_SQUARES; j++) {
      if (b->get_value(j) == EMPTY) {
        continue;
      }

      if (b->get_value(i) == b->get_value(j)) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  Board b(NUMBER_OF_SQUARES, &STATE_LIST, &validator);
  Board* solution = b.find_solution();

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
