#include "bfs.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

// przeszukiwanie grafu wszerz, by ustalic czy jest spojny
int breadth_first_search(graph* g){
    int* queue; // kolejka
    int* visited; // lista odwiedzonych wezlow
    int q_counter = 0; // odpowiada za wyjmowanie z kolejki
    int j = 0; // odpowiada za dodawania do kolejki
    int i, current_root;
    int rc = g->col * g->row;

    queue = (int*) malloc(sizeof(int) * rc * 4); // to nie jest zbyt wydajne jesli chodzi o pamiec, ale dziala
    visited = (int*) malloc(sizeof(int) * rc);

    for (i = 0; i < rc; i++){
        visited[i] = 0;
    }

    for (i = 0; i < rc*4; i++){
        queue[i] = -1;
    }

    // zaczynamy od 0 wezla
    visited[0] = 1;
    for (i = 0; i <= 4; i++){ // dodajemy do kolejki wezly z ktorymi jest polaczony
        if (g->links[0][i] != -1){
            queue[j++] = g->links[0][i];
        }
    }

    while (queue[q_counter] != -1){
        current_root = queue[q_counter++]; // bierzemy wezel z kolejki
        if (visited[current_root] != 1){ // sprawdzamy czy byl juz odwiedzany
            visited[current_root] = 1;

            for (i = 0; i <= 4; i++){ // dodajemy do kolejki wezly polaczone z obecnym, jesli nie byly jeszcze odwiedzane
                if (g->links[current_root][i] != -1 && visited[g->links[current_root][i]] == 0){
                queue[j++] = g->links[current_root][i];
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
    free(queue);
    return 1;
}