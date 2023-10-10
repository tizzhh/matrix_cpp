CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17
LFLAGS = -lgtest -lgtest_main -lpthread

.PHONY: clean all rebuild

ifeq ($(shell uname), Linux)
LFLAGS += -lpthread -lsubunit -lm
endif

all: libs21_matrix_oop.a

test: libs21_matrix_oop.a s21_tests_oop.o
	$(CXX) s21_tests_oop.o $(LFLAGS) -L. -ls21_matrix_oop -o $@
	./test

gcov_report: clean add_gcov_flags test
	./test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open gcov_report/index.html

add_gcov_flags:
	$(eval CXXFLAGS += --coverage)
	$(eval LFLAGS += -lgcov)

libs21_matrix_oop.a: s21_matrix_oop.a
	mv $^ $@

s21_matrix_oop.a: s21_matrix_oop.o
	ar -rcs $@ $^

s21_matrix_oop.o: s21_matrix_oop.cpp
	$(CXX) -c $(CXXFLAGS) $^

s21_tests_oop.o: s21_tests_oop.cpp
	$(CXX) -c $(CXXFLAGS) $^

clean:
	rm -rf *.o test gcov_report *.gcda *.gcno coverage.info *.a a.out

rebuild: clean all
