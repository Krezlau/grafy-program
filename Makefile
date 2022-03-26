all:
	gcc src/*.c -o bin/grafy-program -Wall -pedantic
test:
	gcc import-test/main.c src/graph.c src/import.c -Wall -pedantic -o bin/import-test -ggdb
