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
    q->elements = NULL;
    q->nbElements = 0;
    return q;
}

/* offer()
 * adds a node at the end of the queue.
 */
void offer(queue_t *q, void *n) {
    if (q->nbElements <= 0) {
        q->elements = malloc(sizeof(void *) * (q->nbElements + 1));
    } else {
        q->elements = realloc(q->elements, sizeof(void *) * (q->nbElements + 1));
    }
    if (q->elements == NULL) {
        perror("realloc()");
        exit(EXIT_FAILURE);
    }
    q->elements[q->nbElements] = n;
    q->nbElements++;
}

/* poll()
 * returns the node at the beginning of the queue and removes it.
 */
void *poll(queue_t *q) {
    int size_memory = q->nbElements;
    void **memory = q->elements;
    q->nbElements--;
    q->elements = malloc(sizeof(void *) * q->nbElements);
    if (q->elements == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size_memory - 1; i++) {
        q->elements[i] = memory[i + 1];
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
    free(q->elements);
    q->elements = NULL;
    q->nbElements = 0;
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
    if (q->nbElements > 0) {
        return 0;
    }
    return 1;
}
