//
// Created by guillaume on 06/11/16.
//

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

queue_t* createQueue(){
    queue_t* q =NULL;
    q=malloc(sizeof(queue_t));
    q->listNode=malloc(sizeof(node_t*)*0);
    q->nbNode=0;
    return q;
}

void offer(queue_t* q, node_t* n){
    int sizememory=q->nbNode;
    node_t** memory;
    memory=q->listNode;
    q->nbNode++;
    q->listNode=malloc(sizeof(node_t*)*q->nbNode);
    for(int i=0; i<sizememory; i++){
        q->listNode[i]=memory[i];
    }
    q->listNode[sizememory]=n;
    free(memory);
}

node_t* poll(queue_t* q){
    int sizememory=q->nbNode;
    node_t** memory;
    memory=q->listNode;
    q->nbNode--;
    q->listNode=malloc(sizeof(node_t*)*q->nbNode);
    for(int i=0; i<sizememory-1; i++){
        q->listNode[i]=memory[i+1];
    }
    node_t* value = memory[0];
    free(memory);
    return value;
}

void clear(queue_t* q){
    free(q->listNode);
    q->listNode=malloc(sizeof(node_t*)*0);
}

void free_queue(queue_t* q){
    free(q->listNode);
    free(q);
}

int isEmpty(queue_t* q){
    if(q->nbNode>0){
        return 0;
    }
    return 1;
}

void printQueue(queue_t* queue){
    printf("Nodes :\n");
    for(int i=0; i<queue->nbNode; i++){
        printNode(queue->listNode[i]);
    }
}


