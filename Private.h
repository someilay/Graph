#ifndef GRAPH_PRIVATE_H
#define GRAPH_PRIVATE_H

struct private{
    void** privateField;
} typedef Private;

Private* createPrivate(int n);
void* destroyPrivate(Private* aPrivate);

#endif