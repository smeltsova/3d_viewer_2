CXX = g++
CXX_FLAGS = -std=c++17
EFLAGS = -Wall -Werror -Wextra
TFLAGS = -lgtest -lgtest_main
DEBUG = -g
SRC_FILES = model/affinity.cc model/parser.cc model/object.cc model/model.cc controller/controller.cc
TEST_FILES = tests/test_affinity.cc tests/test_parser.cc tests/test_model.cc tests/test_controller.cc

APP=3DViewer_2.app
ifeq ($(shell uname), Linux)
APP=3DViewer_2
endif

.PHONY:
	all install uninstall dvi dist test clean gcov_report valgrind build check_style fix_style

all: clean tests

test: clean
	${CXX} ${CXX_FLAGS} ${EFLAGS} ${DEBUG} ${SRC_FILES} ${TEST_FILES} -o test ${TFLAGS}
	./test

build:
	rm -rf build
	mkdir build
	cmake -S . -B build && cmake --build build

install: uninstall build
	mkdir ~/Desktop/3D_Viewer_2.0
	cp -rf ./build/3DViewer_2.app ~/Desktop/3D_Viewer_2.0

uninstall:
	rm -rf ~/Desktop/3D_Viewer_2.0

dvi: doxy
	open docs/doxygen/html/index.html

doxy:
	doxygen docs/Doxyfile

dist:
	mkdir -p 3D_Viewer_2.0
	mkdir -p 3D_Viewer_2.0/src
	cp -rf controller model docs models tests view CMakeLists.txt main.cc Makefile 3D_Viewer_2.0/src
	tar -cvzf 3D_Viewer_2.0.tar 3D_Viewer_2.0/
	mv 3D_Viewer_2.0.tar ~/Desktop/3D_Viewer_2.0.tar
	rm -rf 3D_Viewer_2.0


gcov_report: clean
	$(CXX) $(EFLAGS) ${SRC_FILES} --coverage -g -O0 $(TEST_FILES) -o gcov_report $(TFLAGS)
	./gcov_report
	gcovr
	gcovr --filter model/ --exclude-throw-branches --html-details coverage.html
	open coverage.html

valgrind:
	${CXX} ${CXX_FLAGS} ${EFLAGS} ${DEBUG} ${SRC_FILES} ${TEST_FILES} -o test ${TFLAGS}
	valgrind --leak-check=full -s test

check_style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(shell find . -name "*.cc") $(shell find . -name "*.cpp") $(shell find . -name "*.h")
	rm -rf .clang-format

fix_style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(shell find . -name "*.cc") $(shell find . -name "*.cpp") $(shell find . -name "*.h")
	rm -rf .clang-format

clean:
	rm -rf *.a *.o test *.css coverage*.html gcov_report *.gcno *.gcda *.dSYM .clang-format build CMakeLists.txt.user docs/doxygen 3D_Viewer_2.0