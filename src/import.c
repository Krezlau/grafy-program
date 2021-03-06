#include "graph.h"
#include "import.h"
#include <stdlib.h>
#include <stdio.h>

// pomocne funkcje do importu

int check_if_integer_greater_than(char temp[], int number, int n){
    int i = 0;
    while (i < n){
        if ((temp[i] < 48 || temp[i] > 57) && temp[i] != 45){
            return 0;
        }
        i++;
    }
    if (atoi(temp) <= number){
        return 0;
    }
    return 1;
}

int check_if_double_greater_than_zero(char* temp, int n){
    int i = 0;
    int dot_counter = 0;
    while (i < n){
        if ((temp[i] < '0' || temp[i] > '9') && temp[i] != '.'){
            return 0;
        }
        if (temp[i] == '.'){
            dot_counter++;
        }
        if (dot_counter > 1){
            return 0;
        }
        i++;
    }
    if(strtod(temp, NULL) <= 0){
        return 0;
    }
    return 1;
}

// sprawdza czy wezly sa obok siebie w grafie
int check_if_valid_connection(int current_node, char* temp, int col, int row, int n){
    if (check_if_integer_greater_than(temp, -1, n)){
        int node = atoi(temp);
        if (node < row * col){
            int pos = check_node_position(current_node, col, row);
            switch (pos)
            {
            case -9:
                if (node == current_node + 1 || node == current_node + col){
                    return 1;
                }
                else{
                    return 0;
                }
                break;
            case -10:
                if (node == current_node + 1 || node == current_node + col || node == current_node - 1){
                    return 1;
                }
                else{
                    return 0;
                }
                break;
            case -11:
                if (node == current_node - 1 || node == current_node + col){
                    return 1;
                }
                else{
                    return 0;
                }
                break;
            case 1:
                if (node == current_node + 1 || node == current_node + col || node == current_node - col){
                    return 1;
                }
                else{
                    return 0;
                }
                break;
            case 0:
                if (node == current_node + 1 || node == current_node + col || node == current_node - 1 || node == current_node - col){
                    return 1;
                }
                else{
                    return 0;
                }
                break;
            case -1:
                if (node == current_node - 1 || node == current_node + col || node == current_node - col){
                    return 1;
                }
                else{
                    return 0;
                }
                break;
            case 11:
                if (node == current_node + 1 || node == current_node - col){
                    return 1;
                }
                else{
                    return 0;
                }
                break;
            case 10:
                if (node == current_node + 1 || node == current_node - col || node == current_node - 1){
                    return 1;
                }
                else{
                    return 0;
                }
                break;
            case 9:
                if (node == current_node - 1 || node == current_node - col){
                    return 1;
                }
                else{
                    return 0;
                }
                break;
            default:
                break;
            }
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
    return 0;
}

// sprawdza pozycje wezla i w zaleznosci od niej zwraca wartosci:
//  -9  1   11
//  -10 0   10
//  -11 -1  9
int check_node_position(int node, int col, int row){
    int pos_x, pos_y;
    if (node % col == 0){
        pos_y = 1;
    }
    else if(node % col == col-1){
        pos_y = -1;
    }
    else{
        pos_y = 0;
    }
    if (node < col){
        pos_x = -1;
    }
    else if (node >= row*col - col){
        pos_x = 1;
    }
    else{
        pos_x = 0;
    }
    return pos_x*10 + pos_y; 
}
