#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

// na razie nie lapie bledow w pliku :(

// pomocnicza do wczytywania danych z pliku
void reset_temp(char* temp, int i){
    while (i >= 0){
        temp[i--] = '\0';
    }
}

// tworzy graf o podanych wymiarach
graph* create_graph(int col, int row){
    int i, j;
    int rc = row * col;
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
        for (i = 0; i < rc; i++){
            for (j = 0; j < 5; j++){
                loaded_graph->links[i][j] = -1;
                loaded_graph->weights[i][j] = -1;
            }
        }
    }
    return loaded_graph;
}

// zwalnianie pamieci
void free_graph(graph* g){
    int i;
	for (i = 0; i < g->row * g->col; i++)
		free(g->links[i]);
	free(g->links);
    for (i = 0; i < g->row * g->col; i++)
		free(g->weights[i]);
	free(g->weights);
	free(g);
}

// import z pliku
graph* import_graph(char* file_path){
    FILE *in = fopen(file_path, "r");
    char temp[100];
    int c, j = 0;
    int line = 0;
    int i = 0;
    int row, col;
    
    graph* loaded_graph = NULL;
    // wczytywanie liczby kolumn i wierszy
    c = fgetc(in);
    while(c != '\n'){
        if (c != ' '){
            temp[i++] = c;
        }
        else{
            col = atoi(temp);
            reset_temp(temp, i);
            i = 0;
        }
        c = fgetc(in);
    }
    row = atoi(temp);
    reset_temp(temp, i);
    i = 0;
    line++;
    // tworzymy graf o podanych wymiarach
    loaded_graph = create_graph(col, row);
    if (loaded_graph == NULL){
        return loaded_graph;
    }
    // wczytywanie poszczegolnych krawedzi
    c = fgetc(in);
    while (c != EOF){
        if (c == '\n'){
            line++;
            j = 0;
        }
        if (isdigit(c)){
            temp[i++] = c;
            c = fgetc(in);
            while (isdigit(c)){
                temp[i++] = c;
                c = fgetc(in);
            }
            c = fgetc(in);
            if (c == ':'){
                // po liczbie wystepuje : wiec ta liczba to wezel z ktorym wystepuje krawedz
                loaded_graph->links[line-1][j++] = atoi(temp);
                reset_temp(temp, i);
                i = 0;
                // wczytujemy wage tej krawedzi
                c = fgetc(in);
                while (isdigit(c) || c == '.'){
                    temp[i++] = c;
                    c = fgetc(in);
                }
                loaded_graph->weights[line-1][j-1] = strtod(temp, NULL); //strtod konwertuje na double
                reset_temp(temp, i);
                i = 0;
                continue;
            }
            else{
                // jesli nie ma dwukropka skladnia jest niepoprawna
                fclose(in);
                printf("ERROR");
            }
        }
        c = fgetc(in);
    }
    fclose(in);
    return loaded_graph;
}

// export do pliku
void export_graph(char* file_path, graph* g){
    FILE *out = fopen(file_path, "w");
    int i, j;

    // kolumny i wiersze
    fprintf(out, "%d %d\n", g->col, g->row); 

    // poszczególne krawędzie
    for (i = 0; i < g->col * g->row; i++){
        fprintf(out, "\t");
        j = 0;
        while (g->links[i][j] != -1){
            fprintf(out, " %d :%.16g ", g->links[i][j], g->weights[i][j]);
            j++;
        }
        fprintf(out, "\n");
    }
    fclose(out);
}