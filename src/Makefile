CXX = g++
CXX_FLAGS = -std=c++17
EFLAGS = -Wall -Werror -Wextra
TFLAGS = -lgtest -lgtest_main
MFLAGS = -fsanitize=address
DEBUG = -g
SRC_FILES = model/affinity.cc model/parser.cc model/object.cc model/model.cc controller/controller.cc
TEST_FILES = tests/test_affinity.cc tests/test_parser.cc tests/test_model.cc tests/test_controller.cc

.PHONY:
	all install uninstall dvi dist test clean gcov_report valgrind build check_style fix_style

all: clean tests

test: clean
	${CXX} ${CXX_FLAGS} ${EFLAGS} ${DEBUG} ${SRC_FILES} ${TEST_FILES} -o test ${MFLAGS} ${TFLAGS}
	./test

build:
	rm -rf build
	mkdir build
	cmake -S . -B build && cmake --build build

install: uninstall build
	mkdir ~/Desktop/3D_Viewer_2
	cp -rf ./build ~/Desktop/3D_Viewer_2

uninstall:
	rm -rf ~/Desktop/3D_Viewer_2

dvi: doxy
	open docs/doxygen/html/index.html

doxy:
	doxygen docs/Doxyfile

dist:


gcov_report: clean
	$(CXX) $(EFLAGS) ${SRC_FILES} --coverage -g -O0 $(TEST_FILES) -o gcov_report $(TFLAGS)
	./gcov_report
	gcovr
	gcovr --filter model/ --exclude-throw-branches --html-details coverage.html
	open coverage.html

valgrind:
	${CXX} ${CXX_FLAGS} ${EFLAGS} ${DEBUG} ${SRC_FILES} ${TEST_FILES} -o test ${MFLAGS} ${TFLAGS}
	valgrind --leak-check=full -s test

check_style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.h *.cc controller/*.h controller/*.cc model/*.h model/*.cc tests/*.h tests/*.cc view/*.h view/*.cc main.cc
	rm -rf .clang-format

fix_style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.h *.cc controller/*.h controller/*.cc model/*.h model/*.cc tests/*.h tests/*.cc view/*.h view/*.cc main.cc
	rm -rf .clang-format

clean:
	rm -rf *.a *.o test *.css coverage*.html gcov_report *.gcno *.gcda .clang-format build