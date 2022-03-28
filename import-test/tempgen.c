#include "../src/graph.h"
#include "../src/import.h"
#include "../src/bfs.h"
#include "../src/gen.h"
#include "../src/queue.h"

#include <stdio.h>
#include <stdlib.h>

graph* generate_graph(int col, int row, double r1, double r2){
    graph* loaded_graph = create_graph(col, row);

    int current_node;

    if (col != 1 && row != 1){
        for (current_node = 0; current_node < col*row; current_node++){
            switch (check_node_position(current_node, row, col))
            {
            case -9:
                loaded_graph->links[current_node][0] = current_node + 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
                loaded_graph->links[current_node][1] = current_node + row;
                loaded_graph->weights[current_node][1] = randomizer(r1,r2);
                break;
            
            case -10:
                loaded_graph->links[current_node][0] = current_node + 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
                loaded_graph->links[current_node][1] = current_node + row;
                loaded_graph->weights[current_node][1] = randomizer(r1,r2);
                loaded_graph->links[current_node][2] = current_node - 1;
                loaded_graph->weights[current_node][2] = randomizer(r1,r2);
                break;

            case -11:
                loaded_graph->links[current_node][0] = current_node - 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
                loaded_graph->links[current_node][1] = current_node + row;
                loaded_graph->weights[current_node][1] = randomizer(r1,r2);
                break;

            case 1:
                loaded_graph->links[current_node][0] = current_node + 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
                loaded_graph->links[current_node][1] = current_node + row;
                loaded_graph->weights[current_node][1] = randomizer(r1,r2);
                loaded_graph->links[current_node][2] = current_node - row;
                loaded_graph->weights[current_node][2] = randomizer(r1,r2);
                break;

            case 0:
                loaded_graph->links[current_node][0] = current_node + 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
                loaded_graph->links[current_node][1] = current_node + row;
                loaded_graph->weights[current_node][1] = randomizer(r1,r2);
                loaded_graph->links[current_node][2] = current_node - 1;
                loaded_graph->weights[current_node][2] = randomizer(r1,r2);
                loaded_graph->links[current_node][3] = current_node - row;
                loaded_graph->weights[current_node][3] = randomizer(r1,r2);
                break;    

            case -1:
                loaded_graph->links[current_node][0] = current_node - 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
                loaded_graph->links[current_node][1] = current_node + row;
                loaded_graph->weights[current_node][1] = randomizer(r1,r2);
                loaded_graph->links[current_node][2] = current_node - row;
                loaded_graph->weights[current_node][2] = randomizer(r1,r2);
                break;

            case 11:
                loaded_graph->links[current_node][0] = current_node + 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
                loaded_graph->links[current_node][1] = current_node - row;
                loaded_graph->weights[current_node][1] = randomizer(r1,r2);
                break;

            case 10:
                loaded_graph->links[current_node][0] = current_node - 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
                loaded_graph->links[current_node][1] = current_node + 1;
                loaded_graph->weights[current_node][1] = randomizer(r1,r2);
                loaded_graph->links[current_node][2] = current_node - row;
                loaded_graph->weights[current_node][2] = randomizer(r1,r2);
                break;

            case 9:
                loaded_graph->links[current_node][0] = current_node - 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
                loaded_graph->links[current_node][1] = current_node - row;
                loaded_graph->weights[current_node][1] = randomizer(r1,r2);
                break;

            default:
                break;
            }
        }
    }
    else if (col == 1 && row != 1){
        for (current_node = 0; current_node < col*row; current_node++){
            if (current_node == 0){
                loaded_graph->links[current_node][0] = current_node + 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
            }
            else if (current_node == row - 1){
                loaded_graph->links[current_node][0] = current_node - 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
            }
            else{
                loaded_graph->links[current_node][0] = current_node - 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
                loaded_graph->links[current_node][1] = current_node + 1;
                loaded_graph->weights[current_node][1] = randomizer(r1,r2);
            }
        }
    }
    else if (col != 1 && row == 1){
        for (current_node = 0; current_node < col*row; current_node++){
            if (current_node == 0){
                loaded_graph->links[current_node][0] = current_node + 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
            }
            else if (current_node == col - 1){
                loaded_graph->links[current_node][0] = current_node - 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
            }
            else{
                loaded_graph->links[current_node][0] = current_node - 1;
                loaded_graph->weights[current_node][0] = randomizer(r1,r2);
                loaded_graph->links[current_node][1] = current_node + 1;
                loaded_graph->weights[current_node][1] = randomizer(r1,r2);
            }
        }
    }
    return loaded_graph;
}