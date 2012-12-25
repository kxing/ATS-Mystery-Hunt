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
// The Thermometers puzzle with the Braille constraint can be found at:
// http://web.mit.edu/puzzle/www/12/puzzles/a_circus_line/blackout/
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
#include <time.h>

#include "include/board.h"
#include "include/state.h"
#include "include/state_list.h"

#include "tests/mystery_hunt/braille_board.h"

State* ALL_STATES[NUMBER_OF_STATES];

void create_all_states() {
  char pretty_print_string[2] = {'\0', '\0'};
  for (int i = 0; i < NUMBER_OF_STATES; i++) {
    pretty_print_string[0] = 'A' + i;
    ALL_STATES[i] = new State(pretty_print_string);
  }
}

void delete_all_states() {
  for (int i = 0; i < NUMBER_OF_STATES; i++) {
    delete ALL_STATES[i];
  }
}

const StateList STATE_LIST(ALL_STATES, NUMBER_OF_STATES);

// Fine-grained board.
enum SmallSquareType {
  SMALL_EMPTY,
  SMALL_FILLED,
  SMALL_UNFILLED,
};

const SmallSquareType BRAILLE[NUMBER_OF_STATES]
                             [BRAILLE_ROWS]
                             [BRAILLE_COLUMNS] = {
  {    // Braille A.
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
  }, { // Braille B.
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
  }, { // Braille C.
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
  }, { // Braille D.
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
  }, { // Braille E.
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_UNFILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
  }, { // Braille F.
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
  }, { // Braille G.
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
  }, { // Braille H.
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
  }, { // Braille I.
    {SMALL_UNFILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
  }, { // Braille J.
    {SMALL_UNFILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
  }, { // Braille K.
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
  }, { // Braille L.
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
  }, { // Braille M.
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
  }, { // Braille N.
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
  }, { // Braille O.
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_UNFILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
  }, { // Braille P.
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
  }, { // Braille Q.
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
  }, { // Braille R.
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
  }, { // Braille S.
    {SMALL_UNFILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
  }, { // Braille T.
    {SMALL_UNFILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
  }, { // Braille U.
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_FILLED},
  }, { // Braille V.
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_FILLED},
  }, { // Braille W.
    {SMALL_UNFILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_FILLED},
  }, { // Braille X.
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_UNFILLED},
    {SMALL_FILLED, SMALL_FILLED},
  }, { // Braille Y.
    {SMALL_FILLED, SMALL_FILLED},
    {SMALL_UNFILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_FILLED},
  }, { // Braille Z.
    {SMALL_FILLED, SMALL_UNFILLED},
    {SMALL_UNFILLED, SMALL_FILLED},
    {SMALL_FILLED, SMALL_FILLED},
  },
};

SmallSquareType get_small_square_type(const Board* const board, int index) {
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
    if (get_small_square_type(board, i) == SMALL_FILLED) {
      min_sum++;
      max_sum++;
    } else if (get_small_square_type(board, i) == SMALL_EMPTY) {
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
    if (get_small_square_type(board, bottom) == SMALL_UNFILLED &&
        get_small_square_type(board, next) == SMALL_FILLED) {
      return false;
    }
    bottom += step;
    next += step;
  }
  return true;
}

bool validator(const Board* const board) {
  // Row 1.
  if (!valid_line(board, 0, 9, 1, 6)) {
    return false;
  } else if (!valid_thermometer(board, 2, 6, 1)) {
    return false;
  } else if (!valid_thermometer(board, 7, 9, 1)) {
    return false;
  }

  // Row 3.
  if (!valid_line(board, 20, 29, 1, 6)) {
    return false;
  }

  // Row 4.
  if (!valid_line(board, 30, 39, 1, 8)) {
    return false;
  } else if (!valid_thermometer(board, 31, 33, 1)) {
    return false;
  }

  // Row 5.
  if (!valid_line(board, 40, 49, 1, 5)) {
    return false;
  } else if (!valid_thermometer(board, 45, 42, -1)) {
    return false;
  }

  // Row 6.
  if (!valid_thermometer(board, 52, 53, 1)) {
    return false;
  } else if (!valid_thermometer(board, 56, 54, -1)) {
    return false;
  }

  // Row 7.
  if (!valid_line(board, 60, 69, 1, 5)) {
    return false;
  } else if (!valid_thermometer(board, 60, 62, 1)) {
    return false;
  } else if (!valid_thermometer(board, 63, 66, 1)) {
    return false;
  } else if (!valid_thermometer(board, 67, 69, 1)) {
    return false;
  }

  // Row 8.
  if (!valid_line(board, 70, 79, 1, 6)) {
    return false;
  } else if (!valid_thermometer(board, 70, 73, 1)) {
    return false;
  } else if (!valid_thermometer(board, 74, 76, 1)) {
    return false;
  }

  // Row 9.
  if (!valid_line(board, 80, 89, 1, 4)) {
    return false;
  } else if (!valid_thermometer(board, 80, 85, 1)) {
    return false;
  }

  // Row 10.
  if (!valid_line(board, 90, 99, 1, 6)) {
    return false;
  } else if (!valid_thermometer(board, 95, 93, -1)) {
    return false;
  }

  // Row 11.
  if (!valid_line(board, 100, 109, 1, 6)) {
    return false;
  } else if (!valid_thermometer(board, 108, 107, -1)) {
    return false;
  }

  // Row 12.
  if (!valid_line(board, 110, 119, 1, 4)) {
    return false;
  } else if (!valid_thermometer(board, 119, 116, -1)) {
    return false;
  }

  // Row 13.
  if (!valid_thermometer(board, 129, 127, -1)) {
    return false;
  }

  // Row 14.
  if (!valid_line(board, 130, 139, 1, 6)) {
    return false;
  } else if (!valid_thermometer(board, 133, 130, -1)) {
    return false;
  } else if (!valid_thermometer(board, 137, 138, 1)) {
    return false;
  }

  // Row 15.
  if (!valid_line(board, 140, 149, 1, 2)) {
    return false;
  } else if (!valid_thermometer(board, 140, 144, 1)) {
    return false;
  } else if (!valid_thermometer(board, 148, 146, -1)) {
    return false;
  }

  // Column 1.
  if (!valid_thermometer(board, 50, 0, -10)) {
    return false;
  } else if (!valid_thermometer(board, 120, 90, -10)) {
    return false;
  }

  // Column 2.
  if (!valid_line(board, 1, 141, 10, 5)) {
    return false;
  } else if (!valid_thermometer(board, 21, 1, -10)) {
    return false;
  } else if (!valid_thermometer(board, 51, 41, -10)) {
    return false;
  } else if (!valid_thermometer(board, 121, 91, -10)) {
    return false;
  }

  // Column 3.
  if (!valid_line(board, 2, 142, 10, 9)) {
    return false;
  } else if (!valid_thermometer(board, 22, 12, -10)) {
    return false;
  } else if (!valid_thermometer(board, 122, 92, -10)) {
    return false;
  }

  // Column 4.
  if (!valid_line(board, 3, 143, 10, 9)) {
    return false;
  } else if (!valid_thermometer(board, 13, 23, 10)) {
    return false;
  } else if (!valid_thermometer(board, 103, 123, 10)) {
    return false;
  }

  // Column 5.
  if (!valid_thermometer(board, 34, 14, -10)) {
    return false;
  } else if (!valid_thermometer(board, 104, 134, 10)) {
    return false;
  }

  // Column 6.
  if (!valid_line(board, 5, 145, 10, 6)) {
    return false;
  } else if (!valid_thermometer(board, 15, 35, 10)) {
    return false;
  } else if (!valid_thermometer(board, 125, 105, -10)) {
    return false;
  } else if (!valid_thermometer(board, 135, 145, 10)) {
    return false;
  }

  // Column 7.
  if (!valid_line(board, 6, 146, 10, 9)) {
    return false;
  } else if (!valid_thermometer(board, 16, 46, 10)) {
    return false;
  } else if (!valid_thermometer(board, 106, 86, -10)) {
    return false;
  } else if (!valid_thermometer(board, 136, 126, -10)) {
    return false;
  }

  // Column 8.
  if (!valid_line(board, 7, 147, 10, 6)) {
    return false;
  } else if (!valid_thermometer(board, 17, 37, 10)) {
    return false;
  } else if (!valid_thermometer(board, 57, 47, -10)) {
    return false;
  } else if (!valid_thermometer(board, 77, 97, 10)) {
    return false;
  }

  // Column 9.
  if (!valid_line(board, 8, 148, 10, 10)) {
    return false;
  } else if (!valid_thermometer(board, 58, 18, -10)) {
    return false;
  } else if (!valid_thermometer(board, 98, 78, -10)) {
    return false;
  }

  // Column 10.
  if (!valid_line(board, 9, 149, 10, 8)) {
    return false;
  } else if (!valid_thermometer(board, 19, 39, 10)) {
    return false;
  } else if (!valid_thermometer(board, 59, 49, -10)) {
    return false;
  } else if (!valid_thermometer(board, 109, 79, -10)) {
    return false;
  } else if (!valid_thermometer(board, 139, 149, 10)) {
    return false;
  }

  return true;
}

int main() {
  clock_t start = clock();
  create_all_states();
  int search_order[NUMBER_OF_SQUARES] = {
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 1, 6, 21, 0, 5, 20, 4, 9, 24, 2, 3, 7, 8, 22, 23,
  };

  Board board(NUMBER_OF_SQUARES, &STATE_LIST, search_order, &validator);
  get_small_square_type(&board, 0);
  Board* solution = board.find_solution();

  if (solution == NULL) {
    // Found no solution.
    printf("No solution found\n");
  } else {
    // Found a solution - print it out, four to a line.
    solution->pretty_print(5);
    delete solution;
  }
  delete_all_states();
  clock_t end = clock();

  printf("Time taken: %f seconds.\n", (float)(end - start) / CLOCKS_PER_SEC);
  return 0;
}
