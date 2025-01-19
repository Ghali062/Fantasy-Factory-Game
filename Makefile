CC = g++ -g
CCFLAGS = -Wall -Werror
LIBFLAGS =
SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)
EXEC = fantasy-factory-game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LIBFLAGS)

%.o: %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

.depends:
	g++ -MM $(SRC) > .depends

-include .depends

testcase:
	cd tests; make run

clean:
	rm -f $(OBJ) $(EXEC)

distclean:
	cd tests; make clean
	rm -f $(OBJ) $(EXEC)
