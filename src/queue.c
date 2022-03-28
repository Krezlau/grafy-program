#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// implementacja circular queue

queue* create_queue(int size){
    queue* q = (queue*) malloc(sizeof(queue));
    q->front = -1;
    q->rear = -1;
    q->size = size;
    q->items = (int*) malloc(sizeof(int) * size);
    return q;
}

void free_queue(queue* q){
    free(q->items);
    free(q);
}

int isFull(queue* q){
    if((q->front == q->rear + 1) || (q->front == 0 && q->rear == q->size -1)){
        return 1;
    }
    return 0;
}

int isEmpty(queue* q){
    if(q->front == -1){
        return 1;
    }
    return 0;
}

int enQueue(queue* q, int thingy){
    if(isFull(q)){
        return -1;
    }
    if(q->front == -1){
        q->front = 0;
    }
    q->rear = (q->rear + 1) % q->size;
    q->items[q->rear] = thingy;
    return 0;
}

int deQueue(queue* q, int* thingy){
    if(isEmpty(q)){
        return -1;
    }
    (*thingy) = q->items[q->front];
    if(q->front == q->rear){
        q->front = -1;
        q->rear = -1;
    }
    else{
        q->front = (q->front + 1) % q->size;
    }
    return 0;
}

int count_elements(queue* q){
    int counter = 0;
    if(isEmpty(q)){
        return 0;
    }
    if(isFull(q)){
        return q->size;
    }
    for (int i = q->front; i != q->rear; i = (i + 1) % q->size){
        counter++;
    }
    return counter+1;
}