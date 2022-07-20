.PHONY: all clean tests check valgrind_check gcov_report dvi dist rebuild install uninstall 

CC=gcc 
CFLAGS=-c -std=c11
LDFLAGS=-Wall -Wextra -Werror 
LIBFLAGS=`pkg-config --cflags --libs check` -lm

CFILES= s21_matrix.c stack.c stack_i.c parser.c test.c
OFILES=$(CFILES:.c=.o)
TARGET = tests

default: rebuild

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) -o $(TARGET) $(LIBFLAGS)

%.o: %.c
	$(CC) $(LDFLAGS) $(CFLAGS)  $<

valgrind_check:
	$(CC) -O0 -g  $(LDFLAGS) $(CFILES) -o $(TARGET) $(LIBFLAGS)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET) -n file
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./$(TARGET) -n file

gcov_report: 
	$(CC) --coverage $(LDFLAGS) $(CFILES) -o $(TARGET) $(LIBFLAGS)
	./$(TARGET)
	lcov -t "$(TARGET)" -o $(TARGET).info -c -d ./
	genhtml -o report $(TARGET).info
	open report/index.html

check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	rm -rf *.o *.out *.cfg
	CK_FORK=no leaks --atExit -- ./$(TARGET)

dvi:
	open report.md  

dist: 
	mkdir 3DViewer_v1; mkdir 3DViewer_v1/src
	cp *.c *.h *.cpp *.ui *.pro Makefile *.md 3DViewer_v1/src
	tar -cvzf 3DViewer_v1.tar.gz 3DViewer_v1/
	mv 3DViewer_v1.tar.gz $(HOME)/Desktop/
	@ rm -rf 3DViewer_v1/

install:
	mkdir ../build
	cp $(TARGET) ../build/$(TARGET)

uninstall: 
	@ rm -rf ../build

clean:
	rm -rf $(TARGET)  s21_calc *.a *.o *.out *.cfg fizz *.gc* *.info report CPPLINT.cfg ../build

rebuild: clean uninstall all install
