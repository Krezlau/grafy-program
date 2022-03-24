#include "../src/graph.h"
#include "../src/import.h"
#include <stdio.h>

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
    graph* testgraph[11];
    int correct_ef[11] = {11, 11, 11, 12, 12, 13, 14, 12, 14, 13, 0};
    char files[11][100] = {"graphs/blad1", "graphs/blad2", "graphs/blad3", "graphs/blad4", "graphs/blad5", "graphs/blad6", "graphs/blad7", "graphs/blad8", "", "graphs/blad10", "graphs/mygraph.txt" };

    for (int i = 0; i < 11; i++){
        testgraph[i] = import_graph(files[i]);
        if (errorflag == correct_ef[i]){
            printf("TEST %d: PASSED\n", i + 1);
        }
        else{
            printf("TEST %d: %d FAILED\n", i + 1, errorflag);
        }
        errorflag = 0;
    }
    
    for (int i = 0; i < 11; i++){
        free_graph(testgraph[i]);
    }
    return 0;
}
