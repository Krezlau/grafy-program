#include "graph.h"
#include "bfs.h"
#include "import.h"
#include "gen.h"
#include "dijkstra.h"

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <ctype.h>



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
		for (int i = 0; i < 10; i++){
			array_of_user_input[i] = 0;
		}
		int err = 0;
	    graph* loaded_graph;

	while((opt = getopt (argc, argv, "k:w:f:t:i:bs:e:o:h")) != -1)
	{
		switch (opt)
		{
			case 'k':
				number_of_columns = atoi(optarg);
				array_of_user_input[0] = 1;
				break;
			case 'w':
				number_of_rows = atoi(optarg);
				array_of_user_input[1] = 1;
				break;
			case 'f':
				range_from = atof(optarg);
				array_of_user_input[2] = 1;
				break;
			case 't':
				range_to = atof(optarg);
				array_of_user_input[3] = 1;
				break;
			case 'i':
				input = optarg;
				err = import_graph(input, &loaded_graph);
				array_of_user_input[4] = 1;
				break;
			case 'b':
				is_bfs = 1;	
				array_of_user_input[5] = 1;		
				break;
			case 's': 
				starting_knot = atoi(optarg);
				array_of_user_input[6] = 1;
			case 'e': 
				ending_knot = atoi(optarg);
				array_of_user_input[7] = 1;
			case 'o':
				out = optarg;
				array_of_user_input[8] = 1;
				break;
			case 'h':
				fprintf(stdout, instructions, Program_name);
				exit(EXIT_FAILURE);
			
            default:
            fprintf(stderr,"\nUzytkownik podal argumenty w niewlasciwy sposob\n");
			fprintf(stdout, instructions, Program_name);
            return 3;
		}
	}
		
	if(array_of_user_input[4] == 1)
	{
		
		err = import_graph(input, &loaded_graph);
		if(err == 11)
		{
			fprintf(stderr,"blad wymiaru(1,2,3)\n");
			free_graph(loaded_graph);
			return 11;
		} 
		else if(err == 12)
		{
			fprintf(stderr,"blad polaczenia wezlow(4,5,6)\n");
			free_graph(loaded_graph);
			return 12;
		}
		else if(err == 13)
		{
			fprintf(stderr,"blad zapisu wagi(6,10)\n");
			free_graph(loaded_graph);
			return 13;
		}
		else if(err == 14)
		{
			fprintf(stderr,"plik pusty lub nie istnieje(7,9)\n");
			free_graph(loaded_graph);
			return 14;
		}
	}
	else 
    {
		
		if(array_of_user_input[0] == 1 && array_of_user_input[1] == 1 && array_of_user_input[2] == 1 && array_of_user_input[3] == 1) // sprawdzamy czy uzytkownik podal wszystkie wartosci
		{																															// do generacji grafu jesli nie to program generuje graf 
            ;																														// uzywajac wartosci domyslnych
        }
        else
        {
            fprintf(stdout, "\nUzytkownik nie podal wszystkich wartosci do generacji grafu \ndlatego wartosci ktorych nie podal uzytkownik zostana ustawione jako domyslne\nk = 10, w = 10, zakres od 0, zakres do 1\n ");
        }
        if(number_of_columns > 0 && number_of_rows > 0 && range_from >= 0 && range_to > 0) //jesli uzytkownik wprowadzil poprawne wartosci do generowania grafu 
        {																					// to graf zostanie wygenerowany za pomoca funkcji creating_graph
            loaded_graph = creating_graph( number_of_columns, number_of_rows, range_from, range_to);
			
        }
        else
        {
        	fprintf(stderr,"\nUzytkownik podal wartosci ujemne!\nNalezy podac wartosci dodatnie\n");//uzytkownik chce zeby graf sie zrobil 0 x 0 lub range_to = 0
            free_graph(loaded_graph);																//nie spelnia wymagan generacji grafu
			return 2;                                                                               
        }
	}
	
	
    if (is_bfs == 1)
	{
		if(breadth_first_search(loaded_graph) == 1)
		{
			fprintf(stdout, "\npodany graf jest spojny\n");    //stwierdzenie i wyswietlenie na ekran czy podany graf jest spojny czy nie
    	}
    	else
		{
        	fprintf(stdout, "\npodany graf jest niespojny\n");
    	}
	} 	
	if(array_of_user_input[6] == 1 && array_of_user_input[7] == 1)
	{
		if(starting_knot >= 0 && ending_knot >= 0)
		{
			if(starting_knot > (number_of_columns * number_of_rows - 1) || ending_knot > (number_of_columns * number_of_rows - 1))
			{
				fprintf(stderr,"\nWartosci szukanych wezlow musza istniec!\n");
				return 7;
			}
			vertex_links_result(starting_knot, ending_knot, loaded_graph);//przekaz wezel poczatkowy i koncowy do dijk zeby poszukac najkrotszej drogi
																		  //wyswietla na stdout wezel poczatkowy i koncowy oraz sume wag krawedzi pomiedzy nimi
		}
		else
		{
			if(starting_knot < 0 && ending_knot < 0)
			{
				fprintf(stderr,"\nWartosci wezlow nie moga byc ujemne!\n");
				return 6;
			}
			if(starting_knot >= 0)
				;
			else
			{
				fprintf(stderr, "\nWartosc poczatkowego wezla nie moze byc mniejsza niz 0!\n");
				return 4;
			}
	
			if(ending_knot >= 0)
				;
			else
			{
				fprintf(stderr, "\nWartosc koncowego wezla nie moze byc mniejsza niz 0!\n");
				return 5;
			}
		}
	}
    if(array_of_user_input[8] == 1)
	{
		export_graph(out, loaded_graph); //eksport grafu do pliku

	}	
    

	free_graph(loaded_graph);

    
    return 0;
}
