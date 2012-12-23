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

#include "state.h"
#include "state_list.h"

class Board;

typedef const State* Square;
typedef bool (*BoardValidator)(const Board* const);

class Board {
 public:
  Board(const int number_of_squares,
        const StateList* const state_list,
        const int* const search_order,
        BoardValidator validator);
  ~Board();

  Square get_value(int index) const {
    assert(is_valid_index(index));
    assert(state_list->is_valid_state(squares[index]));

    return squares[index];
  }

  void set_value(int index, Square value) {
    assert(is_valid_index(index));
    assert(state_list->is_valid_state(value));

    squares[index] = value;
  }

  bool is_empty(int index) const {
    assert(is_valid_index(index));
    return (squares[index] == EMPTY);
  }

  // Returns a board containing the solution, if it exists.
  // Returns NULL if there is no solution.
  // The caller is responsible for freeing the pointer, if it is non-NULL.
  Board* find_solution() const;

  // Prints the board.
  void pretty_print() const;

 private:
  const int number_of_squares;
  const StateList* const state_list;

  // Array of int pointers, with length |number_of_squares|.
  const int* const search_order;

  // Array of State* pointers, with length |number_of_squares|.
  Square* const squares;

  // Function to check if the state of the Board is reasonable.
  BoardValidator validator;

  // Returns a copy of the board. The caller is responsible for freeing the
  // memory allocated.
  Board* copy() const;

  // Returns a board containing the solution, if it exists.
  // Returns NULL if there is no solution.
  // The caller is responsible for freeing the pointer, if it is non-NULL.
  bool find_solution_internal(int index);

  #ifndef NDEBUG
  bool is_valid_index(int index) const {
    return (0 <= index) && (index < number_of_squares);
  }
  #endif
};

#endif  // _BOARD_H_
