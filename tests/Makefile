# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g -Wall -Werror -I..

# Executable name
EXEC = testcase

# Source files
SRCS = testcase.cc ../rawMaterials.cc

# Header files
HDRS = ../rawMaterials.hh

# Object files
OBJS = testcase.o rawMaterials.o

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
testcase.o: testcase.cc $(HDRS)
	$(CXX) $(CXXFLAGS) -c testcase.cc

rawMaterials.o: ../rawMaterials.cc $(HDRS)
	$(CXX) $(CXXFLAGS) -c ../rawMaterials.cc -o rawMaterials.o

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Run the test case
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run