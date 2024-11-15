CC=g++ -Wall -Werror -Wextra -std=c++17 -g
CHECKFLAGS=-lgtest -lgmock -pthread
GCOVFLAGS = -fprofile-arcs -ftest-coverage
GCOV=--coverage
OS = $(shell uname)

all: install

install:
	rm -rf build*
	mkdir build
	cd Mazy && qmake && make && make clean && rm Makefile && cd ../ && mv Mazy/mazy.app build

uninstall: clean
	rm -rf build*

tests: clean
	$(CC) tests/tests.cpp Mazy/filehandler.cpp Mazy/generationperfectmaze.h Mazy/maze.cpp Mazy/mazesolver.cpp $(CHECKFLAGS) -o tests/tests
	./tests/tests
	rm -rf tests/tests

dvi:
	open README.html

dist:
	rm -rf Archive_Mazy/
	mkdir Archive_Mazy/
	mkdir Archive_Mazy/src
	cp -r ./build/Mazy.app Archive_Mazy/src/
	tar cvzf Archive_Mazy.tgz Archive_Mazy/
	rm -rf Archive_Mazy/

check:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(shell find . -name "*.cpp" -or -name "*.cc" -or -name "*.h" -or -name "*.h")
	clang-format -n $(shell find . -name "*.cpp" -or -name "*.cc" -or -name "*.h" -or -name "*.h") --verbose -Werror
	rm .clang-format

clean:
	rm -f *.gcno *.gcda *.info *.out *.gch *.tgz
	rm -rf ./gcov_rep.out.dSYM
	rm -rf ./report
	rm -rf ./*.o ./*.a
	rm -rf tests/tests
	rm -rf .clang-format
	rm -rf Mazy/Mazy.pro.user
