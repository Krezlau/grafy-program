all:
	gcc src/*.c -o bin/grafy-program -Wall -pedantic
test:
	gcc import-test/main.c src/graph.c src/import.c src/bfs.c src/queue.c src/gen.c -Wall -pedantic -o bin/test -ggdb
