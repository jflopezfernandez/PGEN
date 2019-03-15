
SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cpp .hpp

vpath %.cpp src
vpath %.hpp include

# TODO: Remove this on release. Users expect to be able to customize program
# compilation, which these explicit flags prevent.
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

PROGRAM = pgen

all: $(PROGRAM)

$(PROGRAM): main.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ -lboost_program_options

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -I include $(TARGET_ARCH) -c -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o $(PROGRAM)

