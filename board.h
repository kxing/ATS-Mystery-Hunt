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

#ifndef _BOARD_H_
#define _BOARD_H_

#include <assert.h>

typedef int square_t;

const square_t EMPTY = 0;

class Board {
 public:
  // The states of the board must be from 1 to |number_of_states| inclusive.
  Board(int number_of_squares, int number_of_states, bool (*validator)(Board*));
  ~Board();

  square_t get_value(int index) {
    assert(0 <= squares[index]);
    assert(squares[index] <= number_of_states);
    return squares[index];
  }

  void set_value(int index, square_t value) {
    assert(0 <= value);
    assert(value <= number_of_states);
    squares[index] = value;
  }

  // Returns a board containing the solution, if it exists.
  // Returns NULL if there is no solution.
  // The caller is responsible for freeing the pointer, if it is non-NULL.
  Board* find_solution();

 private:
  int number_of_squares;
  int number_of_states;
  square_t* squares;

  bool (*validator)(Board*);

  // Returns a copy of the board. The caller is responsible for freeing the
  // memory allocated.
  Board* copy();

  // Returns a board containing the solution, if it exists.
  // Returns NULL if there is no solution.
  // The caller is responsible for freeing the pointer, if it is non-NULL.
  Board* find_solution_internal(int index);
};

#endif  // _BOARD_H_
