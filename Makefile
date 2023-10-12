CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
LFLAGS = -lgtest -lgtest_main -fprofile-arcs

.PHONY: clean all rebuild test gcov_report

ifeq ($(shell uname), Linux)
LFLAGS += -lpthread -lsubunit -lm
endif

all: libs21_matrix_oop.a

test: libs21_matrix_oop.a s21_tests_oop.o
	$(CXX) s21_tests_oop.o $(LFLAGS) -L. -ls21_matrix_oop -o $@
	./test

libs21_matrix_oop.a: s21_matrix_oop.a
	mv $^ $@

s21_matrix_oop.a: s21_matrix_oop.o
	ar -rcs $@ $^

s21_matrix_oop.o: s21_matrix_oop.cpp
	$(CXX) -c $(CXXFLAGS) $(COVERAGE_FLAGS) $^

s21_tests_oop.o: s21_tests_oop.cpp
	$(CXX) -c $(CXXFLAGS) $^

gcov_report: test
	./test
	lcov -c -d . -o coverage.info --no-external
	lcov --remove coverage.info '/usr/*' --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open gcov_report/index.html

clean:
	rm -rf *.o test gcov_report *.gcda *.gcno coverage.info *.a a.out

rebuild: clean all
