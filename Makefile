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
CXX_FLAGS := -Wall -I./

LIB_OBJECTS := board.o state.o state_list.o

EXAMPLE_EXECUTABLE := example
EXAMPLE_SOURCE := tests/example.cpp
EXAMPLE_OBJECT := example.o

NURIKABE_SIMPLE_EXECUTABLE := nurikabe_simple
NURIKABE_SIMPLE_SOURCE := tests/nurikabe_simple.cpp
NURIKABE_SIMPLE_OBJECT := nurikabe_simple.o

THERMOMETERS_SIMPLE_EXECUTABLE := thermometers_simple
THERMOMETERS_SIMPLE_SOURCE := tests/thermometers_simple.cpp
THERMOMETERS_SIMPLE_OBJECT := thermometers_simple.o

BRAILLE_BOARD_SOURCE := tests/mystery_hunt/braille_board.cpp
BRAILLE_BOARD_OBJECT := braille_board.o

NURIKABE_EXECUTABLE := nurikabe
NURIKABE_SOURCE := tests/mystery_hunt/nurikabe.cpp
NURIKABE_OBJECT := nurikabe.o

THERMOMETERS_EXECUTABLE := thermometers
THERMOMETERS_SOURCE := tests/mystery_hunt/thermometers.cpp
THERMOMETERS_OBJECT := thermometers.o

ALL_EXECUTABLES := \
      $(EXAMPLE_EXECUTABLE) \
      $(NURIKABE_SIMPLE_EXECUTABLE) \
      $(THERMOMETERS_SIMPLE_EXECUTABLE) \
      $(NURIKABE_EXECUTABLE) \
      $(THERMOMETERS_EXECUTABLE)

ifeq ($(NDEBUG), 1)
  CXX_FLAGS += -O3 -DNDEBUG
else
  CXX_FLAGS += -O0 -g
endif

all: $(ALL_EXECUTABLES) 

# ------------------------------------------------------------------------------
# Library source files.
# ------------------------------------------------------------------------------

board.o: include/board.cpp
	$(CXX) $(CXX_FLAGS) -c include/board.cpp

state.o: include/state.cpp
	$(CXX) $(CXX_FLAGS) -c include/state.cpp

state_list.o: include/state_list.cpp
	$(CXX) $(CXX_FLAGS) -c include/state_list.cpp

# ------------------------------------------------------------------------------
# Test files.
# ------------------------------------------------------------------------------

$(EXAMPLE_OBJECT): $(EXAMPLE_SOURCE)
	$(CXX) $(CXX_FLAGS) -c $(EXAMPLE_SOURCE)

$(EXAMPLE_EXECUTABLE): $(LIB_OBJECTS) $(EXAMPLE_OBJECT)
	$(CXX) $(LIB_OBJECTS) $(EXAMPLE_OBJECT) -o $(EXAMPLE_EXECUTABLE)

$(NURIKABE_SIMPLE_OBJECT): $(NURIKABE_SIMPLE_SOURCE)
	$(CXX) $(CXX_FLAGS) -c $(NURIKABE_SIMPLE_SOURCE)

$(NURIKABE_SIMPLE_EXECUTABLE): $(LIB_OBJECTS) $(NURIKABE_SIMPLE_OBJECT)
	$(CXX) $(LIB_OBJECTS) $(NURIKABE_SIMPLE_OBJECT) \
      -o $(NURIKABE_SIMPLE_EXECUTABLE)

$(THERMOMETERS_SIMPLE_OBJECT): $(THERMOMETERS_SIMPLE_SOURCE)
	$(CXX) $(CXX_FLAGS) -c $(THERMOMETERS_SIMPLE_SOURCE)

$(THERMOMETERS_SIMPLE_EXECUTABLE): $(LIB_OBJECTS) $(THERMOMETERS_SIMPLE_OBJECT)
	$(CXX) $(LIB_OBJECTS) $(THERMOMETERS_SIMPLE_OBJECT) \
      -o $(THERMOMETERS_SIMPLE_EXECUTABLE)

# Braille board for some 2012 Mystery Hunt puzzles.
$(BRAILLE_BOARD_OBJECT): $(BRAILLE_BOARD_SOURCE)
	$(CXX) $(CXX_FLAGS) -c $(BRAILLE_BOARD_SOURCE)

$(NURIKABE_OBJECT): $(NURIKABE_SOURCE)
	$(CXX) $(CXX_FLAGS) -c $(NURIKABE_SOURCE)

$(NURIKABE_EXECUTABLE): $(LIB_OBJECTS) \
                        $(BRAILLE_BOARD_OBJECT) \
                        $(NURIKABE_OBJECT)
	$(CXX) $(LIB_OBJECTS) $(BRAILLE_BOARD_OBJECT) $(NURIKABE_OBJECT) \
      -o $(NURIKABE_EXECUTABLE)

$(THERMOMETERS_OBJECT): $(THERMOMETERS_SOURCE)
	$(CXX) $(CXX_FLAGS) -c $(THERMOMETERS_SOURCE)

$(THERMOMETERS_EXECUTABLE): $(LIB_OBJECTS) \
                            $(BRAILLE_BOARD_OBJECT) \
                            $(THERMOMETERS_OBJECT)
	$(CXX) $(LIB_OBJECTS) $(BRAILLE_BOARD_OBJECT) $(THERMOMETERS_OBJECT) \
      -o $(THERMOMETERS_EXECUTABLE)

# ------------------------------------------------------------------------------
# Clean.
# ------------------------------------------------------------------------------

clean: 
	rm -f *.o $(ALL_EXECUTABLES)
