#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"
#include "import.h"

int errorflag = 0;

// pomocnicza do wczytywania danych z pliku
void reset_temp(char* temp, int i){
    while (i >= 0){
        temp[i--] = '\0';
    }
}

// mozliwe bledy:
// 1 wymiary nie sa liczbami calkowitymi
// 2 wymiary mniejsze lub rowne zero
// 3 podano za duzo wymiarow
// 4 polaczenie z wezlem ktory nie graniczy z zadanym wezlem
// 5 polaczenie z wezlem ktory nie istnieje (liczba ujemna lub wieksza rowna rozmiarowi)
// 6 niepoprawny zapis wagi (strtod nie dziala)
// 7 plik jest pusty
// 8 za duzo wezlow
// 9 plik nie istnieje
// 10 brak dwukropka/ brak wagi

// blad 11: blad wymiarow (1,2,3)
// blad 12: blad polaczenia wezlow (4,5,8)
// blad 13: blad zapisu wagi (6,10)
// blad 14: plik pusty lub nie istnieje (7,9)

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
    if(g != NULL){
        for (i = 0; i < g->row * g->col; i++)
            free(g->links[i]);
        free(g->links);
        for (i = 0; i < g->row * g->col; i++)
            free(g->weights[i]);
        free(g->weights);
        free(g);
    }
}

// import z pliku
graph* import_graph(char* file_path){
    FILE *in = fopen(file_path, "r");
    if (in == NULL){
        errorflag = 14;
        return NULL;
    }
    char temp[2048];
    int c, j = 0;
    int line = 0;
    int i = 0;
    int row, col;
    
    graph* loaded_graph = NULL;
    // wczytywanie liczby kolumn i wierszy
    int values_counter = 0;
    c = fgetc(in);
    if (c == EOF){
        errorflag = 14;
        return NULL;
    }
    while(line == 0){
        if (c != ' ' && c != '\n'){
            temp[i++] = c;
        }
        else{
            if (values_counter == 0 || values_counter == 1){
                if (check_if_integer_greater_than(temp, -1) == 1){
                    if ( values_counter == 0){
                        col = atoi(temp);
                    }
                    else{
                        row = atoi(temp);
                    }
                    reset_temp(temp, i);
                    i = 0;
                    values_counter++;
                }
                else{
                    reset_temp(temp, i);
                    i = 0;
                    errorflag = 11;
                    fclose(in);
                    return NULL;
                }
            }
            else{
                reset_temp(temp, i);
                i = 0;
                errorflag = 11;
                fclose(in);
                return NULL;
            }
        }
        if(c == '\n'){
            line ++;
        }
        c = fgetc(in);
    }
    
    // tworzymy graf o podanych wymiarach
    loaded_graph = create_graph(col, row);
    if (loaded_graph == NULL){
        return loaded_graph;
    }
    // wczytywanie poszczegolnych krawedzi
    c = fgetc(in);
    while (c != EOF){
        if (line > row*col){
            reset_temp(temp, i);
            i = 0;
            errorflag = 12;
            return NULL;
        }
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
                if (check_if_valid_connection(line-1, temp, row, col)){
                    loaded_graph->links[line-1][j++] = atoi(temp);
                    reset_temp(temp, i);
                    i = 0;
                    // wczytujemy wage tej krawedzi
                    c = fgetc(in);
                    while (c != ' ' && c!= '\n'){
                        temp[i++] = c;
                        c = fgetc(in);
                    }
                    if(check_if_double_greater_than_zero(temp)){
                        loaded_graph->weights[line-1][j-1] = strtod(temp, NULL); //strtod konwertuje na double
                        reset_temp(temp, i);
                        i = 0;
                        continue;
                    }
                    else{
                        reset_temp(temp,i);
                        errorflag = 13;
                        fclose(in);
                        return NULL;
                    }
                }
                else{
                    reset_temp(temp, i);
                    errorflag = 12;
                    fclose(in);
                    return NULL;
                }
            }
            else{
                // jesli nie ma dwukropka skladnia jest niepoprawna
                fclose(in);
                errorflag = 13;
                return NULL;
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
