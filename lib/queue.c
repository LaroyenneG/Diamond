//
// Created by Guillaume LAROYENNE on 06/11/16.
//

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

queue_t *createQueue() {
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }
    q->listNode = NULL;
    q->nbNode = 0;
    return q;
}

/* offer()
 * adds a node at the end of the queue.
 */
void offer(queue_t *q, node_t *n) {
    if (q->nbNode <= 0) {
        q->listNode = malloc(sizeof(void *) * (q->nbNode + 1));
    } else {
        q->listNode = realloc(q->listNode, sizeof(void *) * (q->nbNode + 1));
    }
    if (q->listNode == NULL) {
        perror("realloc()");
        exit(EXIT_FAILURE);
    }
    q->listNode[q->nbNode] = n;
    q->nbNode++;
}

/* poll()
 * returns the node at the beginning of the queue and removes it.
 */
void *poll(queue_t *q) {
    int size_memory = q->nbNode;
    void **memory = q->listNode;
    q->nbNode--;
    q->listNode = malloc(sizeof(void *) * q->nbNode);
    if (q->listNode == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size_memory - 1; i++) {
        q->listNode[i] = memory[i + 1];
    }
    void *value = *memory;

    //free memory
    free(memory);

    return value;
}

/* clear()
 * empty the contents of the queue.
 */
void clear(queue_t *q) {
    free(q->listNode);
    q->listNode = NULL;
    q->nbNode = 0;
}

/* free_queue()
 * releases the memory used by the queue.
 */
void free_queue(queue_t *q) {
    if (q == NULL) {
        return;
    }
    clear(q);
    free(q);

}

/* isEmpty()
 * returns 1 if the queue is empty, else 0.
 */
int isEmpty(queue_t *q) {
    if (q->nbNode > 0) {
        return 0;
    }
    return 1;
}
