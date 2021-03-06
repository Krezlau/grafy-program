#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct graph{
    int col; // kolumny
    int row; // rzedy
    int** links; // krawedzie
    double** weights; // wagi krawedzi
} graph;

void reset_temp(char* temp, int* i);

graph* create_graph(int col, int row);

void free_graph(graph* g);

int import_graph(char* file_path, graph** loaded_graph);

int export_graph(char* file_path, graph* g);

#endif
