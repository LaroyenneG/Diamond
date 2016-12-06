//
// Created by guillaume on 06/11/16.
//

#ifndef PROJETALGOC_QUEUE_H
#define PROJETALGOC_QUEUE_H

#include "diamond.h"

typedef struct queue {
    node_t** listNode;
    int nbNode;
} queue_t;

queue_t* createQueue();
node_t* poll(queue_t* q);
void offer(queue_t* q, node_t* n);
int isEmpty(queue_t* q);
void printQueue(queue_t* queue);
void clear(queue_t* queue);
void free_queue(queue_t* queue);

#endif //PROJETALGOC_QUEUE_H
