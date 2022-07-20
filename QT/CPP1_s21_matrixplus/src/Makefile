.PHONY: all clean test s21_matrix_oop.a check valgrind_check gcov_report rebuild install uninstall 

CC=g++
CFLAGS= -std=c++17

LDFLAGS= -Wall -Wextra -Werror 

OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest`
else
	LIBFLAGS=-lstdc++ -lm -lgtest
endif

CFILES= tests.cpp s21_matrix_oop.cpp
OFILES=$(CFILES:.cpp=.o)
TARGET = tests
LIB_NAME = s21_matrix_oop.a
LIB_FILES = s21_matrix_oop.o

default: test

rebuild: clean all 

all: $(TARGET)

$(LIB_NAME): s21_matrix_oop.o s21_matrix_oop.h
	@ar -rcs $(LIB_NAME) $?
	@ranlib $@
	@cp $@ lib$@

test: rebuild
	./$(TARGET)

$(TARGET): $(OFILES)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OFILES) -o $(TARGET) $(LIBFLAGS)

%.o: %.cpp
	$(CC) -c $(LDFLAGS) $(CFLAGS)  $<

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

check: $(TARGET)
	cppcheck --enable=all  --language=c++ --suppress=missingIncludeSystem *.cpp *.h
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=cpp *.cpp *.h
	rm -rf *.o *.out *.cfg
	CK_FORK=no leaks --atExit -- ./$(TARGET)

install:
	mkdir ../build
	cp $(TARGET) ../build/$(TARGET)

uninstall: 
	@ rm -rf ../build

clean:
	rm -rf $(TARGET)  s21_calc *.a *.o *.out *.cfg fizz *.gc* *.info report CPPLINT.cfg ../build