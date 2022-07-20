.PHONY: all clean test s21_containersplus.a cpplint cppcheck leaks gcov_report rebuild

CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++17
GCOV_FLAG = -fprofile-arcs -ftest-coverage 
LIB_NAME = s21_containersplus
TESTFILE=test

OS = $(shell uname)

ifeq ($(OS), Linux)
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest`
else
	LIBFLAGS=-lstdc++ -lm -lgtest
endif


default: rebuild leaks

all:  $(TESTFILE) 
# check gcov_report


s21_containersplus.a:
	$(CC) -c $(FLAGS) $(LIB_NAME).cpp -o $(LIB_NAME).o
	ar rcs $(LIB_NAME).a $(LIB_NAME).o
	# ranlib $@

rebuild: clean all

$(TESTFILE): s21_containersplus.a
	$(CC) $(FLAGS) $(GCOV_FLAG) $(LIB_NAME).a tests.cpp -o $(TESTFILE) $(LIBFLAGS)
# ./$(TESTFILE)

check: leaks gcov_report cpplint cppcheck

gcov_report: $(TESTFILE)
	lcov --no-external -t "$(TESTFILE)" -o $(TESTFILE).info -c -d ./
	genhtml -o report $(TESTFILE).info
	open report/index.html

cpplint:
	@echo "****** linter start ******"
	cp ../materials/linters/CPPLINT.cfg . 
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.tpp *.h 
	rm -f CPPLINT.cfg

cppcheck:
	@echo "****** cppcheck start ******"
	cppcheck --enable=all --language=c++ --std=c++17 *.cpp  *.h
#cppcheck --enable=all --suppress=constParameter --suppress=useStlAlgorithm --suppress=missingIncludeSystem --suppress=noCopyConstructor --suppress=noOperatorEq --suppress=noExplicitConstructor --suppress=negativeIndex --suppress=missingReturn *.cpp *.tpp *.h
#  --suppress=missingIncludeSystem --suppress=unusedFunction 

clean:
	rm -f *.o *.a *.gcno *.gcda *.info $(TESTFILE) CPPLINT.cfg 
	rm -rf report/

leaks:
ifeq ($(OS), Linux)
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(TESTFILE)
else
	CK_FORK=no leaks -atExit -- ./$(TESTFILE)
endif
