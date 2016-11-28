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

/* offer()
 * adds a node at the end of the queue.
 */
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

/* poll()
 * returns the node at the beginning of the queue and removes it.
 */
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
    free(q->listNode);
    free(q);
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


