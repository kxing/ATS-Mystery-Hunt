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

#ifndef _BRAILLE_BOARD_UTILS_
#define _BRAILLE_BOARD_UTILS_

#include "include/board.h"
#include "tests/mystery_hunt/braille_board.h"

static SmallSquareType get_small_square_type(const Board* const board, int index) {
  int big_row =
      (index / (NUMBER_OF_COLUMNS * BRAILLE_COLUMNS)) / BRAILLE_ROWS;
  int big_column =
      (index % (NUMBER_OF_COLUMNS * BRAILLE_COLUMNS)) / BRAILLE_COLUMNS;
  int small_row =
      (index / (NUMBER_OF_COLUMNS * BRAILLE_COLUMNS)) % BRAILLE_ROWS;
  int small_column = 
      (index % (NUMBER_OF_COLUMNS * BRAILLE_COLUMNS)) % BRAILLE_COLUMNS;

  const State* state = board->get_value(big_row * NUMBER_OF_COLUMNS + big_column);
  if (state == EMPTY) {
    return SMALL_EMPTY;
  }
  
  // Get the Braille pattern associated with the letter.
  char letter = state->get_pretty_print_string()[0];
  return BRAILLE[letter - 'A'][small_row][small_column];
}

#endif  // _BRAILLE_BOARD_UTILS_
