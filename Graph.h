#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#define DIRECTED 1
#define SELF_LOOP 0
#define MULTI_GRAPH 0
#include "Node.h"

struct graph{
    int (*numberOfNodes)(void* this);
    void (*add)(void* this, void* object);
    void (*addEdge)(void* this, int i, int j);
    void* (*remove)(void* this, int i);
    void (*removeEdge)(void* this, int i, int j);
    Node* (*get)(void* this, int i);

} typedef Graph;

Graph* createGraph();

#endif