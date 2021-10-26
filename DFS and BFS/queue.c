#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ll_node_struct {
    int value;
    struct ll_node_struct* next;
} ll_node;

typedef struct queue_struct {
    ll_node* head;
    ll_node* tail;
} queue;

bool is_empty(queue* queue) {
    return queue == NULL || queue->head == NULL;
}

void enqueue(queue* queue, int value) {
    if (queue == NULL) {
        fprintf(stderr, "Invalid queue data structure!\n");
        exit(1);
    }

    ll_node* new = (ll_node*)malloc(sizeof(ll_node));

    if (new == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }

    new->value = value;
    new->next = NULL;

    if (queue->head == NULL) {  // Insert at head and tail.
        queue->head = new;
        queue->tail = new;
    } else {  // Connect and insert at tail.
        queue->tail->next = new;
        queue->tail = new;
    }
}

int dequeue(queue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Invalid queue data structure!\n");
        exit(1);
    }

    if (queue->head == NULL) {
        fprintf(stderr, "Queue is currently empty!\n");
        exit(1);
    }

    ll_node* node = queue->head;
    int val = node->value;
    queue->head = node->next;
    free(node);

    return val;
}
