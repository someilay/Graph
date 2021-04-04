#include <malloc.h>
#include "Node.h"

Node *createNode(void *object) {
    Node *out = malloc(sizeof(Node));

    out->object = object;
    out->adjacencyList = createLinkedList();

    return out;
}