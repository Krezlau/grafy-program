#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gen.h"
#include "graph.h"
//generator wartosci losowych
double randomizer(double start_range, double end_range){
	
	double weight = start_range + (end_range - start_range) * ((double)rand()/ RAND_MAX);
	return weight;
}
//funkcja do generowania wartosci krawedzi
int** array_of_links_generator(int col, int row)
{
    int i, j, k = 0;
    int **temp = (int**) malloc(row * sizeof(int*));
    for(i = 0; i < row; i++)
        temp[i] = (int*) malloc(col * sizeof(int));
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            temp[i][j] = k;
            k++;
        }
    }
    return temp;
}
//sprawdza czy wezel sasiaduje z innymi wezlami
int link_searcher(int** temp, int x, int y, int col, int row, int* visited)
{
    
        if(((x+1) >= 0) && (y >= 0) && ((x+1) < row) && (y < col) && (visited[0] != 1))
        {
            visited[0] = 1;
            return temp[x+1][y];
        }
        else
            visited[0] = 1;
        if((x-1) >= 0 && y >= 0 && (x-1) < row && y < col && visited[1] != 1)
        {
	    visited[1] = 1;	
            return temp[x-1][y];
        }
        else
            visited[1] = 1;
        if(x >= 0 && (y+1) >= 0 && x < row && (y+1) < col && visited[2] != 1)
        {
            visited[2] = 1;
            return temp[x][y+1];
        }
        else
            visited[2] = 1;
        if(x >= 0 && (y-1) >= 0 && x < row && (y-1) < col && visited[3] != 1)
        {
            visited[3] = 1;
            return temp[x][y-1];
        }
        else
            visited[3] = 1;
        return -1;
    

}
//tworzy graf o podanych wymiarach, generuje wartosci krawedzi i wag
graph* creating_graph(int col, int row, double start_range, double end_range){
    int i, j, k, l = 0;
    int rc = row * col;
    int **array_of_links = array_of_links_generator(col, row);
    int *visited = malloc(4 * sizeof(int));
    srand(time(NULL));
    graph* loaded_graph = (graph*) malloc(sizeof(graph));
    if (loaded_graph != NULL) {
        loaded_graph->row = row;
        loaded_graph->col = col;
        loaded_graph->weights = (double**) malloc(sizeof(double*) * rc);
        for (i = 0; i < rc; i++) {
            loaded_graph->weights[i] = (double*) malloc(sizeof(double) * 4);
        }
        loaded_graph->links = (int**) malloc(sizeof(int*) * rc);
        for (i = 0; i < rc; i++){
            loaded_graph->links[i] = (int*) malloc(sizeof(int) * 4);
        }
        for (i = 0; i < row; i++)
        {
            for(k = 0; k < col; k++)
            {
                for (j = 0; j < 4; j++)
                {
                    loaded_graph->links[l][j] = link_searcher(array_of_links, i, k, col, row, visited);
                    loaded_graph->weights[l][j] = randomizer(start_range,end_range);
                }
                visited[0] = 0;
                visited[1] = 0;
                visited[2] = 0;
                visited[3] = 0;
                l++;
            }
        }
    }
    return loaded_graph;
}