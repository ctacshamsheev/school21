.PHONY: all clean tests check valgrind_check gcov_report dvi dist rebuild install uninstall 

CC=gcc 
CFLAGS=-c -std=c11
LDFLAGS=-Wall -Wextra -Werror 
LIBFLAGS=`pkg-config --cflags --libs check` -lm

CFILES= test.c s21_calc.c parser.c stack.c polish_notation.c 
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
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	rm -rf *.o *.out *.cfg
	leaks --atExit -- ./$(TARGET)

dvi:
	open report.md  

dist:
	mkdir calc-1.0
	cp -a -T ./ calc-1.0/    
	tar --totals -cvf calc-1.0.tar calc-1.0
	rm -rf calc-1.0/

install:


uninstall: 


clean:
	rm -rf $(TARGET)  s21_calc *.a *.o *.out *.cfg fizz *.gc* *.info report CPPLINT.cfg calc-1.0.tar calc-1.0/

rebuild: clean all 
