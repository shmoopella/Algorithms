GCC = g++ -std=c++17 -Wall -Werror -Wextra
#GCC = g++ -std=c++17
LIB_FLAGS = -lm -lgtest -lstdc++
TEST_SRC = tests/graph_test.cc
GRAPH_SRC = graph/matrix/s21_matrix_oop.cc \
		graph/s21_graph.cc
ALGORITHM_SRC = graph_algorithms/s21_ant.cc \
 		graph_algorithms/s21_graph_algorithms.cc

all: s21_graph.a s21_graph_algorithms.a test

s21_graph.a:
	$(GCC) -c $(GRAPH_SRC)
	ar rc libs21_graph.a s21_graph.o s21_matrix_oop.o
	ranlib libs21_graph.a
	rm *.o

s21_graph_algorithms.a:
	$(GCC) -c $(ALGORITHM_SRC)
	ar rc libs21_graph_algorithms.a s21_ant.o s21_graph_algorithms.o
	ranlib libs21_graph_algorithms.a
	rm *.o

test:
	$(GCC) $(TEST_SRC) $(GRAPH_SRC) $(ALGORITHM_SRC) $(LIB_FLAGS) -o test && ./test
	rm test.dot test2.dot test

main:
	$(GCC) main.cc $(GRAPH_SRC) $(ALGORITHM_SRC) -o result && ./result

clean:
	rm libs21_graph.a libs21_graph_algorithms.a test test.dot test2.dot result

leak:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test

s21_graph_main:
	$(GCC) main.cc -Lgraph -ls21_graph

s21_matrix.a:
	$(GCC) -c graph/matrix/s21_matrix_oop.cc
	ar rc libs21_matrix.a s21_matrix_oop.o
	ranlib libs21_matrix.a