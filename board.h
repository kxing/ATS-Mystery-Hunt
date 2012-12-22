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

class State;
class StateList;

typedef const State* Square;

extern const State* EMPTY;

class Board {
 public:
  Board(const int number_of_squares,
        const StateList* const state_list,
        bool (*validator)(Board*));
  ~Board();

  Square get_value(int index) const {
    return squares[index];
  }

  void set_value(int index, Square value) {
    squares[index] = value;
  }

  // Returns a board containing the solution, if it exists.
  // Returns NULL if there is no solution.
  // The caller is responsible for freeing the pointer, if it is non-NULL.
  Board* find_solution() const;

 private:
  const int number_of_squares;
  const StateList* const state_list;

  // Array of State* pointers, with length |number_of_squares|.
  Square* const squares;

  // Function to check if the state of the Board is reasonable.
  bool (*validator)(Board*);

  // Returns a copy of the board. The caller is responsible for freeing the
  // memory allocated.
  Board* copy() const;

  // Returns a board containing the solution, if it exists.
  // Returns NULL if there is no solution.
  // The caller is responsible for freeing the pointer, if it is non-NULL.
  bool find_solution_internal(int index);
};

#endif  // _BOARD_H_
