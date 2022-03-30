#include "bfs.h"
#include "graph.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

// przeszukiwanie grafu wszerz, by ustalic czy jest spojny
int breadth_first_search(graph* g){
    queue* queue; // kolejka
    int* visited; // lista odwiedzonych wezlow
    int i, current_root;
    int rc = g->col * g->row;
    int err;
    int size;

    if(g->col >= g->row){
        size = g->row*2 + 1;
    }
    else{
        size = g->col*2 + 1;
    }

    queue = create_queue(size); // z testow wynika ze taka wielkosc kolejki jest wystarczajaca
    visited = (int*) malloc(sizeof(int) * rc);

    for (i = 0; i < rc; i++){
        visited[i] = 0;
    }

    // zaczynamy od 0 wezla
    visited[0] = 1;
    for (i = 0; i < 4; i++){ // dodajemy do kolejki wezly z ktorymi jest polaczony
        if (g->links[0][i] != -1){
            err = enQueue(queue, g->links[0][i]);
        }
    }

    while (!isEmpty(queue)){
        err = deQueue(queue, &current_root); // bierzemy wezel z kolejki
        if (visited[current_root] != 1){ // sprawdzamy czy byl juz odwiedzany
            visited[current_root] = 1;

            for (i = 0; i < 4; i++){ // dodajemy do kolejki wezly polaczone z obecnym, jesli nie byly jeszcze odwiedzane
                if (g->links[current_root][i] != -1 && visited[g->links[current_root][i]] == 0){
                    err = enQueue(queue, g->links[current_root][i]);
                    if (err == -1){
                        printf("enqueue failed aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
                    }
                }
            }
        }
    }

    // sprawdzamy czy wszystkie wezly zostaly odwiedzone
    for (i = 0; i < rc; i++){
        if (visited[i] == 0){
            free(visited);
            free(queue);
            return 0;
        }
    }
    free(visited);
    free_queue(queue);
    return 1;
}