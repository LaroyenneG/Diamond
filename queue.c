//
// Created by guillaume on 06/11/16.
//

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

queue_t* createQueue(){
    queue_t* q=malloc(sizeof(queue_t));
    if(q==NULL){
        perror("malloc()");
        exit(-2);
    }
    q->listNode=malloc(sizeof(node_t*)*0);
    if(q->listNode==NULL){
        perror("malloc()");
        exit(-2);
    }
    q->nbNode=0;
    return q;
}

/* offer()
 * adds a node at the end of the queue.
 */
void offer(queue_t* q, node_t* n){
    q->listNode=realloc(q->listNode, sizeof(node_t*)*(q->nbNode+1));
    if(q->listNode==NULL){
        perror("realloc()");
        exit(-2);
    }
    q->listNode[q->nbNode]=n;
    q->nbNode++;
}

/* poll()
 * returns the node at the beginning of the queue and removes it.
 */
node_t* poll(queue_t* q){
    int sizememory=q->nbNode;
    node_t** memory=NULL;
    memory=q->listNode;
    q->nbNode--;
    q->listNode=malloc(sizeof(node_t*)*q->nbNode);
    if(q->listNode==NULL){
        perror("malloc()");
        exit(-2);
    }
    for(int i=0; i<sizememory-1; i++){
        q->listNode[i]=memory[i+1];
    }
    node_t* value = memory[0];

    //free memory
    free(memory);
    memory=NULL;

    return value;
}

/* clear()
 * empty the contents of the queue.
 */
void clear(queue_t* q){
    free(q->listNode);
    q->listNode=malloc(sizeof(node_t*)*0);
}

/* free_queue()
 * releases the memory used by the queue.
 */
void free_queue(queue_t* q){
    if(q==NULL){
        perror("free_queue()");
        exit(-3);
    }
    free(q->listNode);
    free(q);
    q=NULL;
}

/* isEmpty()
 * returns 1 if the queue is empty, else 0.
 */
int isEmpty(queue_t* q){
    if(q->nbNode>0){
        return 0;
    }
    return 1;
}

/* printQueue()
 * displays all nodes in the queue.
 */
void printQueue(queue_t* queue){
    printf("Nodes :\n");
    for(int i=0; i<queue->nbNode; i++){
        printNode(queue->listNode[i]);
    }
}


