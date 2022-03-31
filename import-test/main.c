#include "../src/graph.h"
#include "../src/import.h"
#include "../src/bfs.h"
#include "../src/gen.h"
#include "../src/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// tutaj sa testy importu

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

// blad 11: blad wymiarow (1,2,3)
// blad 12: blad polaczenia wezlow (4,5,8)
// blad 13: blad zapisu wagi (6)
// blad 14: plik pusty lub nie istnieje (7,9)

int main(int argc, char** argv){
    // test bledow importu
    int lmao;
    if (argc > 1){
        lmao = atoi(argv[1]);
    }
    else{
        lmao = 0;
    }
    if (lmao == 1){
        graph* testgraph[11];
        for (int i = 0; i < 11; i++){
            testgraph[i] = NULL;
        }
        int errorflag;
        int correct_ef[11] = {11, 11, 11, 12, 12, 13, 14, 12, 14, 13, 0};
        char files[11][100] = {"graphs/blad1", "graphs/blad2", "graphs/blad3", "graphs/blad4", "graphs/blad5", "graphs/blad6", "graphs/blad7", "graphs/blad8", "", "graphs/blad10", "graphs/mygraph.txt" };

        for (int i = 0; i < 11; i++){
            errorflag = import_graph(files[i], &testgraph[i]);
            if (errorflag == correct_ef[i]){
                printf("TEST %d: %d PASSED\n", i + 1, errorflag);
            }
            else{
                printf("TEST %d: %d FAILED\n", i + 1, errorflag);
            }
        }
        
        for (int i = 0; i < 11; i++){
            export_graph("graphs/lmao", testgraph[i]);
            free_graph(testgraph[i]);
        }
    }
    

    // test kolejki i generatora
    if (lmao == 2){
        int err;
        srand(time(NULL));
        graph* loaded_graph = NULL;
        for (int i = 0; i < 100; i++){
            int x = rand()%1000 + 1;
            int y = rand()%1000 + 1;
            printf("generating graph: %d, %d\n", x, y);
            loaded_graph = creating_graph(x, y, 1, 2);
            export_graph("graphs/lmao", loaded_graph);
            free_graph(loaded_graph);
            err = import_graph("graphs/lmao", &loaded_graph);
            if (err != 0){
                printf("err: %d\n", err);
            }
            else{
                if(breadth_first_search(loaded_graph) == 1){
                    printf("TAK\n");
                }
                else{
                    printf("NIE\n");
                }
            }
            free_graph(loaded_graph);
        }
    }

    if (lmao == 3){
        graph* loaded_graph = NULL;
        import_graph("graphs/mygraph.txt", &loaded_graph);
        int err = export_graph("graphs/mygraph_out.txt", loaded_graph);
        printf("%d\n", err);
        free_graph(loaded_graph);
    }
    return 0;
}
