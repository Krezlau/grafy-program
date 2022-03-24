all:
	gcc src/*.c -o bin/grafy-program -Wall -pedantic
test:
	gcc funcionaltests/main.c src/graph.c src/import.c -Wall -pedantic -o bin/test -ggdb
