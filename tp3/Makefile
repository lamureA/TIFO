#************************************************
#*                                              *
#*   TP 1&2    (c) 2017 J. FABRIZIO             *
#*                                              *
#*                               LRDE EPITA     *
#*                                              *
#************************************************

CC = g++

CPP_FILES = img.cc pixel.cc
HH_FILES  = img.hh pixel.hh

OBJ_FILES = $(CPP_FILES:.cpp=.o)

CXX_FLAGS += -Wall -Wextra -g -std=c++17

build: $(OBJ_FILES)
	$(CC) main.cc -o tp3 $(OBJ_FILES) $(CXX_FLAGS)

clean:
	rm -f $(OBJ_FILES)
