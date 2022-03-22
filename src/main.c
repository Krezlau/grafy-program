#include "graph.h"
#include "bfs.h"
#include "import.h"
#include <stdio.h>

// narazie tu jest test bfs / importu i exportu

int main(int argc, char** argv){
    graph* loaded_graph1 = import_graph("graphs/niespojny.txt");
    graph* loaded_graph2 = import_graph("graphs/spojny.txt");
    if (breadth_first_search(loaded_graph1) == 1){
        printf("niespojny.txt = spojny\n");
    }
    else{
        printf("niespojny.txt = niespojny\n");
    }
    if (breadth_first_search(loaded_graph2) == 1){
        printf("spojny.txt = spojny\n");
    }
    else{
        printf("spojny.txt = niespojny\n");
    }
    free_graph(loaded_graph1);
    free_graph(loaded_graph2);

    // graph* loaded_graph = import_graph("graphs/mygraph.txt");
    // export_graph("graphs/mygraph_out.txt", loaded_graph);
    // free_graph(loaded_graph);
    return 0;
}
