#include <stdio.h>
#include <stdlib.h>

typedef struct ll_node_struct {
    int value;
    struct ll_node_struct* next;
} ll_node;

typedef struct stack_struct {
    ll_node* head;
} stack;

bool is_empty(stack* stack) {
    return stack == NULL || stack->head == NULL;
}

void push(stack* stack, int value) {
    if (stack == NULL) {
        fprintf(stderr, "Invalid stack data structure!\n");
        exit(1);
    }

    ll_node* new = (ll_node*)malloc(sizeof(ll_node));

    if (new == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }

    new->value = value;
    new->next = stack->head;
    stack->head = new;
}

int pop(stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "Invalid stack data structure!\n");
        exit(1);
    }

    if (stack->head == NULL) {
        fprintf(stderr, "Stack is currently empty!\n");
        exit(1);
    }

    ll_node* node = stack->head;
    int val = node->value;
    stack->head = node->next;
    free(node);

    return val;
}
