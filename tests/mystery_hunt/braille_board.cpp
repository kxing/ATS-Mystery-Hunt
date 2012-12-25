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

#include "tests/mystery_hunt/braille_board.h"

#include "include/state.h"

static State* ALL_STATES[NUMBER_OF_STATES];
const StateList STATE_LIST(ALL_STATES, NUMBER_OF_STATES);

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
