#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct queue{
    int* items;
    int front;
    int rear;
    int size;
} queue;

queue* create_queue(int size);

void free_queue(queue* q);

int isFull(queue* q);

int isEmpty(queue* q);

int enQueue(queue* q, int thingy);

int deQueue(queue* q, int *thingy);

int count_elements(queue* q);

#endif
