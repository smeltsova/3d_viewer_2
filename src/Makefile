CXX = g++
CXX_FLAGS = -std=c++17
EFLAGS = -Wall -Werror -Wextra
TFLAGS = -lgtest -lgtest_main
MFLAGS = -fsanitize=address
DEBUG = -g
SRC_FILES = model/affinity.cc model/object.h
TEST_FILES = tests/test_affinity.cc

.PHONY:
	all install uninstall dvi dist test clean gcov_report valgrind build check_style fix_style

all: clean tests

test: clean
	${CXX} ${CXX_FLAGS} ${EFLAGS} ${DEBUG} ${SRC_FILES} ${TEST_FILES} -o test ${MFLAGS} ${TFLAGS}
	./test

clean:
	rm -rf *.a *.o test *.css coverage*.html gcov_report *.gcno *.gcda .clang-format build