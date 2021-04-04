#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include "LinkedList.h"

#define DIRECTED 1
#define SELF_LOOP 0
#define MULTI_GRAPH 0

struct graph{
    int (*numberOfNodes)(void* this);
    void (*add)(void* this, void* object);
    void (*addEdge)(void* this, int i, int j);
    void* (*remove)(void* this, int i);
    void (*removeEdge)(void* this, int i, int j);
} typedef Graph;

Graph* createGraph();

#endif