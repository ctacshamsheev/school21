.PHONY: all rebuild clean graph_module check
CC=gcc
CFLAGS=-c
LDFLAGS=-Wall -Wextra -Werror 

default: rebuild

all: graph_module

graph_module: graph.o parser.o plot.o stack.o polish_notation.o 
	$(CC) $(LDFLAGS) -lm -o ../build/graph graph.o parser.o plot.o stack.o polish_notation.o -lm
graph.o:
	$(CC) $(CFLAGS) -o graph.o graph.c
polish_notation.o:
	$(CC) $(CFLAGS) -o polish_notation.o polish_notation.c
parser.o:
	$(CC) $(CFLAGS) -o parser.o parser.c
plot.o:
	$(CC) $(CFLAGS) -o plot.o plot.c
stack.o:
	$(CC) $(CFLAGS) -o stack.o stack.c

check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	rm -rf *.o *.out *.cfg
	leaks --atExit -- ../build/graph

clean:
	rm -rf ../build/* *.o *.out *.cfg
rebuild: clean all

