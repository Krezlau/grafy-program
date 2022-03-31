#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>




struct AdjListNode //sasiadujace ze soba wezly
{
    int dest;                   
    double weight;
    struct AdjListNode* next;
};
 

struct AdjList //wskaznik na poczatkowy wezel w liscie sasiedzctwa
{ 
   struct AdjListNode *head;
};
 
struct Graph  //graf skladajacy sie z wierzchoklkow i listy sasiedzctwa
{
    int V;
    struct AdjList* array;
};

struct AdjListNode* Add_node_to_adj_list(int dest, double weight); //dodaj wezel do listy sasiedzctwa

struct Graph* create_temp_graph(int V); //utworz graf za pomoca liczb wierzcholkow

void add_edge_to_graph( struct Graph* graph, int src, int dest, double weight); //dodaj krawedz do grafu wraz z waga

struct MinHeapNode //najmniejszy wezel w kopcu
{
    int  v;
    int dist;
};
 
struct MinHeap //kopiec najmniejszych wartosci()
{
    int size;    //ilosc wezlow w kopcu aktualnie    
    int capacity; //pojemnosc kopca   
    int *pos;   //pozycja potrzebna do funkcji decrease_distance_between_nodes
    struct MinHeapNode **array;
};
struct MinHeapNode* add_node_to_min_heap(int v, int dist); //dodaj wezel do kopca

struct MinHeap* create_min_heap(int capacity); //stworz kopiec

void swap_nodes_in_min_heap(struct MinHeapNode** a, struct MinHeapNode** b); //zamien najmniejszy z drugim najmniejszym wezlem w kopcu

void positions_of_min_heap(struct MinHeap* min_heap, int idx); //aktualizuje pozycje w kopcu

int is_min_heap_empty(struct MinHeap* min_heap); //sprawdza czy kopiec jest pusty

struct MinHeapNode* extract_node_from_min_heap(struct MinHeap* min_heap); //wyciaga najmniejszy wezel z kopca

void decrease_distance_between_nodes(struct MinHeap* min_heap, int v, int dist); //zmniejsza wartosci odleglosci wezla uzywajac pozycji z funkcji positions_of_min_heap

bool is_node_in_min_heap(struct MinHeap *min_heap, int v); //sprawdza czy wierzcholek juz jest w kopcu

void printing_function(double dist[], int n, int start, int end); //drukuje na stdout poczatkowy i koncowy wezel oraz sume wag krawedzi pomiedzy nimi

void dijkstra(struct Graph* graph, int src, int end); //glowna funkcja algorytmu Dijkstry

void vertex_links_result(int start, int end, graph* g); //funkcja wywolujaca algorytm Dijkstry z maina

void converter_graph(graph* g, struct Graph* newgraph); //konwerter grafow

void free_tempGraph(struct Graph* temp_graph);

void free_MinHeap(struct MinHeap* min_heap);

#endif