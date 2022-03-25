#ifndef _GEN_H
#define _GEN_H
#include "graph.h"

double randomizer(double start_range, double end_range);

int** array_of_links_generator(int col, int row);

int link_searcher(int** temp, int x, int y, int col, int row, int* visited);

graph* creating_graph(int col, int row, double start_range, double end_range);



#endif