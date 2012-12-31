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

#include "include/stopwatch/stopwatch.h"

#include <stdio.h>
#include <time.h>

namespace lib_kxing {
namespace stopwatch {

StopWatch::StopWatch() :
    running(false), can_print(false) {
}

StopWatch::~StopWatch() {
}

void StopWatch::start() {
  if (running) {
    printf("Error: calling start() on a StopWatch is already running.\n");
    return;
  }
  running = true;
  can_print = false;
  clock_gettime(CLOCK_MONOTONIC, &start_time);
}

void StopWatch::stop() {
  if (!running) {
    printf("Error: calling stop() on a StopWatch is not running.\n");
    return;
  }
  clock_gettime(CLOCK_MONOTONIC, &stop_time);
  running = false;
  can_print = true;
}

void StopWatch::print_elapsed_time() {
  if (!can_print) {
    printf("Error: calling print_elapsed_time() without calling start()"
           " and stop() immediately before.");
    return;
  }
  long long seconds = (stop_time.tv_sec - start_time.tv_sec);
  long long nanoseconds = (stop_time.tv_nsec - start_time.tv_nsec);
  if (nanoseconds < 0) {
    nanoseconds += 1000000000;
    seconds--;
  }
  printf("Elapsed time: %lld.%09lld seconds\n", seconds, nanoseconds);
}

}  // namespace stopwatch
}  // namespace lib_kxing
