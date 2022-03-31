#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
 
#include "dijkstra.h"

void vertex_links_result(int start, int end, graph* g) //funkcja wywolujaca algorytm Dijkstry z maina
{                                                        
    int V = g->row * g->col;
    struct Graph* graph = create_temp_graph(V);
    converter_graph( g,  graph);
    dijkstra(graph, start, end); //glowna funkcja algorytmu Dijkstry
      
}

void converter_graph(graph* g, struct Graph* newgraph) //konwerter grafow
{
        int i, j;
        for (i = 0; i < g->col * g->row; i++)
        {
            j = 0;
            while ((g->links[i][j] != -1) && (j < 4))
            {
                add_edge_to_graph(  newgraph, i, g->links[i][j], g->weights[i][j]);
                j++;
            }   
        }
}

struct AdjListNode* Add_node_to_adj_list(int dest, double weight) //dodaj wezel do listy sasiedzctwa
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
struct Graph* create_temp_graph(int V) //utworz graf za pomoca liczb wierzcholkow
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
void add_edge_to_graph(struct Graph* graph, int start,int dest, double weight) //dodaj krawedz do grafu wraz z waga
{
    struct AdjListNode* newNode = Add_node_to_adj_list(dest, weight);
    newNode->next = graph->array[start].head;
    graph->array[start].head = newNode;
    newNode = Add_node_to_adj_list(start, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

struct MinHeapNode* add_node_to_min_heap(int v, int dist) //dodaj wezel do kopca
{
    struct MinHeapNode* node_of_min_heap = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node_of_min_heap->v = v;
    node_of_min_heap->dist = dist;
    return node_of_min_heap;
}

struct MinHeap* create_min_heap(int capacity) //stworz kopiec
{
    struct MinHeap* min_heap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    min_heap->pos = (int *)malloc(capacity * sizeof(int));
    min_heap->size = 0;
    min_heap->capacity = capacity;
    min_heap->array = (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return min_heap;
}

void swap_nodes_in_min_heap(struct MinHeapNode** a, struct MinHeapNode** b) //zamien najmniejszy z drugim najmniejszym wezlem w kopcu
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 

void positions_of_min_heap(struct MinHeap* min_heap, int idx) //aktualizuje pozycje w kopcu
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < min_heap->size && min_heap->array[left]->dist < min_heap->array[smallest]->dist )
      smallest = left;
 
    if (right < min_heap->size && min_heap->array[right]->dist < min_heap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        struct MinHeapNode *smallestNode = min_heap->array[smallest]; 
        struct MinHeapNode *idxNode = min_heap->array[idx];  

        min_heap->pos[smallestNode->v] = idx; //zamiana pozycji
        min_heap->pos[idxNode->v] = smallest;

        swap_nodes_in_min_heap(&min_heap->array[smallest], &min_heap->array[idx]); //zamiana wezlow
        positions_of_min_heap(min_heap, smallest);
    }
}
 

int is_min_heap_empty(struct MinHeap* min_heap) //sprawdza czy kopiec jest pusty
{
    return min_heap->size == 0;
}
 
struct MinHeapNode* extract_node_from_min_heap(struct MinHeap* min_heap) //wyciaga najmniejszy wezel z kopca
{
    if (is_min_heap_empty(min_heap))
        return NULL;
 
    struct MinHeapNode* root = min_heap->array[0]; //przechowaj korzen
 
    
    struct MinHeapNode* lastNode = min_heap->array[min_heap->size - 1]; //zamien korzen z ostatnim wezlem
    min_heap->array[0] = lastNode;
 
    min_heap->pos[root->v] = min_heap->size-1; //zaaktualizuj pozycje ostatniego wezla
    min_heap->pos[lastNode->v] = 0;
 
    
    --min_heap->size; //zwolnij niepotrzebne miejsce
    positions_of_min_heap(min_heap, 0);
 
    return root;
}
 

void decrease_distance_between_nodes(struct MinHeap* min_heap, int v, int dist) //zmniejsza wartosci odleglosci wezla uzywajac pozycji z funkcji positions_of_min_heap
{
    int i = min_heap->pos[v]; //potrzebujemy indeks wierzcholka w kopcu
 
    
    min_heap->array[i]->dist = dist; //potrzebujemy wezel i jego aktualne wartosci wag
 
    
    while (i && min_heap->array[i]->dist < min_heap->array[(i - 1) / 2]->dist)
    {
        
        min_heap->pos[min_heap->array[i]->v] = (i-1)/2; //zamien wezly rodzica i syna
        min_heap->pos[min_heap->array[(i-1)/2]->v] = i;
        swap_nodes_in_min_heap(&min_heap->array[i], &min_heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
 

bool is_node_in_min_heap(struct MinHeap *min_heap, int v) //sprawdza czy wierzcholek juz jest w kopcu
{
   if (min_heap->pos[v] < min_heap->size)
     return true;
   return false;
}
 

void printing_function(double weights[], int n, int start, int end) //drukuje na stdout poczatkowy i koncowy wezel oraz sume wag krawedzi pomiedzy nimi
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
    {
        if(i == start)
            fprintf(stdout,"%d \t\t %lf\n", i, weights[i]);
        if(i == end )
            fprintf(stdout,"%d \t\t %lf\n", i, weights[i]);
    }
}
 

void dijkstra(struct Graph* graph, int start, int end) //glowna funkcja algorytmu Dijkstry
{
    int V = graph->V; //potrzebujemy ilosc wierzcholkow (bierzemy ja z iloczynu kolumny razy wiersze)
   
    double weights[V];    
 
    struct MinHeap* min_heap = create_min_heap(V);
    for (int v = 0; v < V; ++v)
    {
        weights[v] = INT_MAX;
        min_heap->array[v] = add_node_to_min_heap(v, weights[v]); //
        min_heap->pos[v] = v;
    }
    min_heap->array[start] = add_node_to_min_heap(start, weights[start]);
    min_heap->pos[start] = start;
    weights[start] = 0;
    decrease_distance_between_nodes(min_heap, start, weights[start]);
    min_heap->size = V; 
    while (!is_min_heap_empty(min_heap))
    {
        struct MinHeapNode* node_of_min_heap = extract_node_from_min_heap(min_heap);
        int u = node_of_min_heap->v;
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
            if (is_node_in_min_heap(min_heap, v) && weights[u] != INT_MAX && pCrawl->weight + weights[u] < weights[v])
            {
                weights[v] = weights[u] + pCrawl->weight;
                decrease_distance_between_nodes(min_heap, v, weights[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 
    printing_function(weights, V, start, end);
    // deleteList(&node_of_min_heap); //proba zwalniania pamieci
}

//proba zwalniania pamieci
// void deleteList(struct AdjListNode** head_ref)
// {
//    /* deref head_ref to get the real head */
//    struct AdjListNode* current = *head_ref;
//    struct AdjListNode* next;
 
//    while (current != NULL)
//    {
//        next = current->next;
//        free(current);
//        current = next;
//    }
   
//    /* deref head_ref to affect the real head back
//       in the caller. */
//    *head_ref = NULL;
// }
