#include <malloc.h>
#include "Graph.h"
#include "Private.h"
#include "LinkedList.h"

#define NUMBER_OF_PRIVATE_FIELDS 1
#define LIST_OF_NODES 0

Graph *createGraph() {
    Graph* out = malloc(sizeof(Graph) + sizeof(void*));
    void** p_out = (void**)out;
    Private* aPrivate = createPrivate(NUMBER_OF_PRIVATE_FIELDS);
    LinkedList* listOfNodes = createLinkedList();

    aPrivate->privateField[LIST_OF_NODES] = listOfNodes;
    p_out[sizeof(Graph) / 4] = aPrivate;

    return out;
}
