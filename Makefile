CFLAGS = -Wall -Werror -Wextra -std=c11
LFLAGS = -lcheck
CC = gcc

.PHONY: clean all rebuild

ifeq ($(shell uname), Linux)
LFLAGS = -lpthread -lcheck -lsubunit -lm
endif

all: libs21_matrix.a

test: libs21_matrix.a tests.o
	$(CC) tests.o $(LFLAGS) -L. -ls21_matrix -o $@

gcov_report: clean add_gcov_flags test
	./test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report

add_gcov_flags:
	$(eval CFLAGS += --coverage)
	$(eval LFLAGS += -lgcov)

libs21_matrix.a: s21_matrix.a
	mv $^ $@

s21_matrix.a: s21_matrix.o
	ar -rcs $@ $^

s21_matrix.o: s21_matrix.c
	$(CC) -c $(CFLAGS) $^

tests.o: tests.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -rf *.o test gcov_report *.gcda *.gcno coverage.info *.a a.out

rebuild: clean all
