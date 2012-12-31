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
// The Braille board has 26 states, one for each letter of the alphabet.
// The board corresponds to a board of pixels, that represents the pixels of
// Braille letters, as shown below:
//
//    0   1 |   2   3 |   4   5 |   6   7 |   8   9
//   10  11 |  12  13 |  14  15 |  16  17 |  18  19
//   20  21 |  22  23 |  24  25 |  26  27 |  28  29
//  --------|---------|---------|---------|--------
//   30  31 |  32  33 |  34  35 |  36  37 |  38  39
//   40  41 |  42  43 |  44  45 |  46  47 |  48  49
//   50  51 |  52  53 |  54  55 |  56  57 |  58  59
//  --------|---------|---------|---------|--------
//   60  61 |  62  63 |  64  65 |  66  67 |  68  69
//   70  71 |  72  73 |  74  75 |  76  77 |  78  79
//   80  81 |  82  83 |  84  85 |  86  87 |  88  89
//  --------|---------|---------|---------|--------
//   90  91 |  92  93 |  94  95 |  96  97 |  98  99
//  100 101 | 102 103 | 104 105 | 106 107 | 108 109
//  110 111 | 112 113 | 114 115 | 116 117 | 118 119
//  --------|---------|---------|---------|--------
//  120 121 | 122 123 | 124 125 | 126 127 | 128 129
//  130 131 | 132 133 | 134 135 | 136 137 | 138 139
//  140 141 | 142 143 | 144 145 | 146 147 | 148 149
//
// -----------------------------------------------------------------------------

#ifndef _BRAILLE_BOARD_H_
#define _BRAILLE_BOARD_H_

#include "include/brute_force_solver/state_list.h"

#define NUMBER_OF_ROWS 5
#define NUMBER_OF_COLUMNS 5
#define NUMBER_OF_SQUARES (NUMBER_OF_ROWS * NUMBER_OF_COLUMNS)

#define BRAILLE_ROWS 3
#define BRAILLE_COLUMNS 2

#define NUMBER_OF_STATES 26

extern const StateList STATE_LIST;

void create_all_states();
void delete_all_states();

// Fine-grained board.
enum SmallSquareType {
  SMALL_EMPTY,
  SMALL_FILLED,
  SMALL_UNFILLED,
};

extern const SmallSquareType BRAILLE[NUMBER_OF_STATES]
                                    [BRAILLE_ROWS]
                                    [BRAILLE_COLUMNS];

#endif  // _BRAILLE_BOARD_H_
