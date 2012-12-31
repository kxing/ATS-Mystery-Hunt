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

#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <time.h>

namespace lib_kxing {
namespace stopwatch {

class StopWatch {
 public:
  StopWatch();
  ~StopWatch();

  void start();
  void stop();
  void print_elapsed_time();

  // Prints out the time it takes to run the given function.
  static void time_function(void (*function)());

 private:
  bool running;
  bool can_print;
  timespec start_time;
  timespec stop_time;
};

}  // namespace stopwatch
}  // namespace lib_kxing

#endif  // _STOPWATCH_H_
