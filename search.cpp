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

const int number_of_squares = 5;
const int number_of_states = 5;

bool validator(Board* b) {
  // Tests for distinct numbers.
  for (int i = 0; i < number_of_squares; i++) {
    if (b->get_value(i) == EMPTY) {
      continue;
    }

    for (int j = i + 1; j < number_of_squares; j++) {
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
  Board b(number_of_squares, number_of_states, &validator);
  Board* solution = b.find_solution();

  if (solution == NULL) {
    // Found no solution.
    printf("No solution found\n");
  } else {
    // Found a solution.
    for (int i = 0; i < number_of_squares; i++) {
      printf("%d ", solution->get_value(i));
    }
    printf("\n");
    delete solution;
  }
  return 0;
}
