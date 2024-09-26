CC=gcc
CFLAGS=-c -std=c11 -Wall -Werror -Wextra
TEST_FLAGS=-lcheck -lpthread -pthread -lm -lgcov -lsubunit

TEST_BIN=tests/*test

SRC0=$(wildcard s21_*.c)
OBJ0=$(patsubst %.c, %.o, $(SRC0))

TEST_SRC=$(wildcard $(TEST_BIN)*.c)
TEST_OBJ=$(patsubst %.c, %.o, $(TEST_SRC))

.PHONY: all clean rebuild

all: s21_matrix.a

s21_matrix.a: $(OBJ0)
	ar rc s21_matrix.a $^
	ranlib s21_matrix.a

test.a: $(TEST_OBJ)
	ar rc $(TEST_BIN).a $^
	ranlib $(TEST_BIN).a

test: clean
	$(CC) $(CFLAGS) --coverage $(SRC0)
	make s21_matrix.a
	make test.a $(TEST_OBJ)
	$(CC) --coverage -o $(TEST_BIN) $(TEST_OBJ) s21_matrix.a $(TEST_FLAGS)
	./$(TEST_BIN)

gcov_report: test
	lcov -t "Test matrix report in src" -o report_src.info -c -d .
	genhtml -o gcov_report report_src.info
	firefox gcov_report/index.html

style: clean
	cp ../materials/linters/.clang-format ../src
	cp ../materials/linters/.clang-format ../src/tests
	clang-format -i *.c *.h
	cd tests && clang-format -i *.c *.h && cd ..
	rm .clang-format tests/.clang-format
	cppcheck --enable=all --suppress=missingIncludeSystem --check-level=exhaustive $(SRC0) $(TEST_SRC)

valgrind: test
ifeq ($(shell uname -s), Linux)
	valgrind -s --leak-check=yes --track-origins=yes ./$(TEST_BIN)
else
	leaks --atExit -- ./$(TEST_BIN)
endif

clean:
	clear
	rm -f *.o *.a *.gcno *.gcda *.info *.html $(TEST_BIN)*.o $(TEST_BIN)*.a $(TEST_BIN)*.gcno $(TEST_BIN)*.gcda $(TEST_BIN) -R gcov_report $(EXE)

rebuild: clean all
