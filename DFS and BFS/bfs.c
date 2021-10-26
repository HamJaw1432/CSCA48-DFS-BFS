#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.c"

// Since the graph is "randomally" generated, we need some parameters.
// Change this number if you want to test with a different graph.
// Domain = [0, 2147483647]
#define RANDOM_SEED 31415

// This is the probability that two nodes have an (undirected) edge.
// Domain = (0, 1]
#define EDGE_PROBABILITY 0.5

// Change this number to increase the node count.
// Domain = [1, 999]
#define NODE_COUNT 10

// This is the source node that we wish to traverse.
// Domain = [0, NODE_COUNT - 1]
#define SOURCE_NODE 0

void print_matrix(bool adjacency_matrix[NODE_COUNT][NODE_COUNT]) {
    printf("      ");
    for (int i = 0; i < NODE_COUNT; i++)
        printf("%3d ", i);

    printf("\n     ");
    for (int i = 0; i < NODE_COUNT; i++)
        printf("----");
    printf("\n");

    for (int i = 0; i < NODE_COUNT; i++) {
        printf("%3d | ", i);
        for (int j = 0; j < NODE_COUNT; j++)
            printf("%3d ", adjacency_matrix[i][j] ? 1 : 0);
        printf("\n");
    }
}

void print_graph_editor_format(bool adjacency_matrix[NODE_COUNT][NODE_COUNT]) {
    printf("--- csacademy graph editor data ---\n");

    for (int i = 0; i < NODE_COUNT; i++)
        printf("%d\n", i);

    for (int i = 0; i < NODE_COUNT; i++) {
        for (int j = (i + 1); j < NODE_COUNT; j++) {
            if (adjacency_matrix[i][j]) {
                printf("%d %d\n", i, j);
            }
        }
    }

    printf("-----------------------------------\n");
}

int main(int argc, char* argv[]) {
    srand(RANDOM_SEED);

    // We represent this graph in the form of an adjancency matrix.
    bool adjacency_matrix[NODE_COUNT][NODE_COUNT];

    // Generate the edges.
    for (int i = 0; i < NODE_COUNT; i++) {
        for (int j = i; j < NODE_COUNT; j++) {
            if (i == j)
                adjacency_matrix[i][j] = false;  // No self edges!
            else {
                bool has_edge = (((double)rand()) / RAND_MAX) < EDGE_PROBABILITY;
                adjacency_matrix[i][j] = has_edge;  // In this case, the matrix is symmertric across the horizontal.
                adjacency_matrix[j][i] = has_edge;

                /**
                 * WARNING:
                 *      SYMMETRY IS NOT ALWAYS GUARENTEED!
                 *      Let's say in an arbitrary graph, we have two nodes and two edges.
                 *      In a directed graph, the weight of travelling to Node Y from Node X could be 4 units.
                 *      However, conversely, travelling from Node X to Node Y could take 8 units.
                 *      Not symmetrical!
                 */
            }
        }
    }

    // Print the matrix out, for visual purposes.
    print_matrix(adjacency_matrix);

    printf("\n");

    // https://csacademy.com/app/graph_editor/
    print_graph_editor_format(adjacency_matrix);
    
    printf("\n");

    // A BFS is done using a queue.
    queue* q = (queue*)calloc(1, sizeof(queue));

    // This is our list of visited nodes.
    bool visited[NODE_COUNT] = {false};

    // Add the first node.
    enqueue(q, SOURCE_NODE);
    visited[SOURCE_NODE] = true;

    // Traverse the graph iteratively.
    while (!is_empty(q)) {
        int current = dequeue(q);  // This is our current node.
        printf("BFS algorithm currently at Node %d ...\n", current);

        for (int i = 0; i < NODE_COUNT; i++) {           // Queue the neighbours of the current node ...
            if (adjacency_matrix[current][i] == true) {  // Only if there's an edge between them ...
                if (visited[i] == false) {               // And the neighbour has not been visited before.
                    enqueue(q, i);
                    visited[i] = true;
                }
            }
        }
    }

    free(q);
}
