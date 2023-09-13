all:
	gcc -o main main.c adjacency_list_2/graph.c algorithms/io_file.c -lm

adjacency_list:
	gcc -o main main.c adjacency_list/graph.c ../data_structures/vector/vector.c

adjacency_matrix:
	gcc -o main main.c adjacency_matrix/graph.c ../data_structures/vector/vector.c

generate_graphviz:
	dot -Tpng graph.dot -o graph.png
