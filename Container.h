#ifndef GRAPH_CONTAINER_H
#define GRAPH_CONTAINER_H

struct container{
    void* object;
    struct container* next;
    struct container* previous;
} typedef Container;

Container* createContainer();
Container* createContainer(void* object, Container* next, Container* previous);

#endif