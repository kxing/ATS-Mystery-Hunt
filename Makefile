# Copyright (c) 2012 Kerry Xing
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

CXX := g++
CXX_FLAGS := -Wall

EXAMPLE_EXECUTABLE := example

ifeq ($(NDEBUG), 1)
  CXX_FLAGS += -O3 -DNDEBUG
else
  CXX_FLAGS += -O0 -g
endif

all: $(EXAMPLE_EXECUTABLE)

board.o: board.cpp
	$(CXX) $(CXX_FLAGS) -c board.cpp

example.o: example.cpp
	$(CXX) $(CXX_FLAGS) -c example.cpp

state.o: state.cpp
	$(CXX) $(CXX_FLAGS) -c state.cpp

state_list.o: state_list.cpp
	$(CXX) $(CXX_FLAGS) -c state_list.cpp

example: board.o example.o state.o state_list.o
	$(CXX) board.o example.o state.o state_list.o -o $(EXAMPLE_EXECUTABLE)

clean: 
	rm -f *.o $(EXAMPLE_EXECUTABLE)
