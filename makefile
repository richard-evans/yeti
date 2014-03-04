#----------------------------------------------------------------------------
#
#                       Makefile for YETI
#
#----------------------------------------------------------------------------

# Compiler (c++11 support required)
GCC=g++-mp-4.7

# LIBS
LIBS=-lstdc++

# Performance Flags
GCC_CFLAGS= -std=c++11 -Wall -O3 -falign-labels -falign-loops -funroll-all-loops -fexpensive-optimizations -funroll-loops -I./hdr
GCC_LDFLAGS= -std=c++11 -lstdc++ -I./hdr -Wall

# Objects
OBJECTS= \
obj/create.o \
obj/initialise.o \
obj/main.o \
obj/material.o \
obj/object.o \
obj/random.o \
obj/scatter.o \
obj/simulate.o

EXECUTABLE=yeti

all: $(OBJECTS) serial

# Serial Targets
serial: $(OBJECTS)
	$(GCC) $(GCC_LDFLAGS) $(LIBS) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS): obj/%.o: src/%.cpp
	$(GCC) -c -o $@ $(GCC_CFLAGS) $<

clean:
	@rm -f obj/*.o
	@rm -f obj/*.o

purge:
	@rm -f obj/*.o
	@rm -f obj/*.o
	@rm -f yeti

tidy:
	@rm -f *~
	@rm -f hdr/*~
	@rm -f src/*~
	@rm -f src/*~
