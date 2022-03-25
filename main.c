#include "graph.h"
#include "bfs.h"
#include "import.h"
#include "gen.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <ctype.h>


// narazie tu jest test bfs / importu i exportu

//Instrukcja obslugi argumentow wywolania programu
char *instructions = 
  "Usage: %s -k [number_of_columns] -w [number_of_rows] -f [starting_value] -t [ending_value] -i [name_of_file_to_read] -b -s [starting_knot] -e [ending_knot] -o [name_of_file_to_write] -h\n"
  "	if -k -w -f -t number_of_columns, number_of_rows, starting_value and ending_value are given then\n"
  "	 	       programs generates graph from these numbers\n"
  "		       also you can't read any file while you are giving the numbers to generate graph\n"
  "	else if -i name_of_the_file_to_read\n"	
  "		       program read the file which is given as name_of_file_to_read\n"
  "	if -b is written then\n"
  "		       program checks if the graph is consistent\n"
  "	if -s -e starting_root ending_root are given then\n"
  "		       program looks for the shortest path between given knots using the Dijkstra algorithm\n"
  "		       the number of the knot have to be higher than zero and have to exist\n"
  "	if -o name_of_file_to_write\n"
  "		       program saves the graph to given file\n";
	
//obsluga argumentow wywolania
int main(int argc, char** argv)
{
        char *Program_name = argv[0];
        int opt;
        char *input = NULL;
        char *out = NULL;
		int is_bfs = 0;
        double range_from = 0;
        double range_to = 1;
		int number_of_columns = 10;
		int number_of_rows = 10;
		int starting_knot = 0;
		int ending_knot = 0;
	    opterr = 0;
	    int array_of_user_input[10];
	    graph* loaded_graph = NULL;

	while((opt = getopt (argc, argv, "k:w:f:t:i:bs:e:o:h")) != -1)
	{
		switch (opt)
		{
			case 'k':
				number_of_columns = atoi(optarg);
				array_of_user_input[0]++;
				
				break;
			case 'w':
				number_of_rows = atoi(optarg);
				array_of_user_input[1]++;
				break;
			case 'f':
				range_from = atof(optarg);
				array_of_user_input[2]++;
				break;
			case 't':
				range_to = atof(optarg);
				array_of_user_input[3]++;
				break;
			case 'i':
				input = optarg;
				import_graph(input);
				array_of_user_input[4]++;
				break;
			case 'b':
				is_bfs = 1;	
				array_of_user_input[5]++;		
				break;
			case 's': //do dokonczenia dijkstra
				starting_knot = atoi(optarg);
				if(starting_knot >= 0)
					break;
				else
				{
					fprintf(stderr, "\nWartosc pierwszego wezla nie moze byc mniejsza niz 0!\n");
					exit(EXIT_FAILURE);
				}
				array_of_user_input[6]++;
			case 'e': //do dokonczenia dijkstra
				ending_knot = atoi(optarg);
				if(ending_knot >= 0)
					break;
				else
				{
					fprintf(stderr, "\nWartosc drugiego wezla nie moze byc mniejsza niz 0!\n");
					exit(EXIT_FAILURE);
				}
				array_of_user_input[7]++;
			case 'o':
				out = optarg;
				array_of_user_input[8]++;
				break;
			case 'h':
				fprintf(stdout, instructions, Program_name);
				exit(EXIT_FAILURE);
			
            default:
            fprintf(stderr,"\nUzytkownik nie podal zadnych argumentow\n");
            abort ();
		}
	}
	if(optind < argc)
	{
		fprintf(stderr, "\nZle parametry wywolania\n");
		for( ;optind < argc; optind++)
			fprintf(stderr, "\t\"%s\"\n", argv[optind]);
		fprintf(stderr, "\n");
		fprintf(stderr, instructions, Program_name);
		exit(EXIT_FAILURE);
	}	
	if(array_of_user_input[4] == 1)
	{
		loaded_graph = import_graph(input);

	}
	else 
    {
		if(array_of_user_input[0] == 1 && array_of_user_input[1] == 1 && array_of_user_input[2] == 1 && array_of_user_input[3] == 1)
        {
            ;
        }
        else
        {
            fprintf(stdout, "\nUzytkownik nie podal wszystkich wartosci do generacji grafu \ndlatego wartosci ktorych nie podal uzytkownik zostana ustawione jako domyslne\nk = 10, w = 10, zakres od = 0, zakres do 1\n ");
        }
        if(number_of_columns > 0 && number_of_rows > 0 && range_from >= 0 && range_to > 0)
        {
            loaded_graph = creating_graph( number_of_columns, number_of_rows, range_from, range_to);
        }
        else
        {
            fprintf(stderr,"\nUzytkownik podal wartosci ujemne!\nNalezy podac wartosci dodatnie\n");//uzytkownik chce zeby graf sie zrobil 0 x 0 lub range_to = 0
            return 2;                                                                               //nie spelnia wymagan generacji grafu
        }
	}
	
	
    if (is_bfs == 1)
	{
		if(breadth_first_search(loaded_graph) == 1)
		{
			fprintf(stdout, "graf jest spojny\n");    
    	}
    	else
		{
        	fprintf(stdout, "graf jest niespojny\n");
    	}
	} 	
    if(array_of_user_input[8] == 1)
	{
		export_graph(out, loaded_graph);

	}	
    free_graph(loaded_graph);


    // graph* loaded_graph = import_graph("graphs/mygraph.txt");
    // export_graph("graphs/mygraph_out.txt", loaded_graph);
    // free_graph(loaded_graph);
    return 0;
}
