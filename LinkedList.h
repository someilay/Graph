#ifndef GRAPH_LINKED_LIST_H
#define GRAPH_LINKED_LIST_H

struct linkedList{
    void (*size)(void* this);
    int (*isEmpty)(void* this);
    void (*addLast)(void* this, void* object);
    void (*add)(void* this, void* object, int i);
    void* (*removeLast)(void* this);
    void* (*remove)(void* this, int i);
    void* (*get)(void* this, int i);
} typedef LinkedList;

LinkedList* createLinkedList();

#endif