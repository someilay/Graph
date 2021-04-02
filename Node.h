#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H
#include "LinkedList.h"

struct node{
    void *object;
    LinkedList* adjacencyList;
} typedef Node;

Node* createNode(void* object);

#endif