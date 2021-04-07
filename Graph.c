#include <malloc.h>
#include "Graph.h"
#include "Private.h"

#define NUMBER_OF_PRIVATE_FIELDS 1
#define LIST_OF_NODES 0

static Private* getPrivate(void* this){
    void** p_this = (void**)this;
    return (Private*)p_this[sizeof(Graph) / 4];
}

static LinkedList* getList(void* this){
    return (LinkedList*)(getPrivate(this)->privateField[LIST_OF_NODES]);
}

static Node* toNode(void* node){
    return (Node*)node;
}

int numberOfNodes(void* this){
    LinkedList* list = getList(this);
    return list->size(list);
}

void addNode(void* this, void* object){
    LinkedList* list = getList(this);
    list->addLast(list, createNode(object));
}

void addEdge(void* this, int i, int j){
    LinkedList* list = getList(this);
#if SELF_LOOP == 0
    if (i == j){
        return;
    }
#endif

    void *vFirst = list->get(list, i);
    void *vSecond = list->get(list, j);

    if (vFirst != NULL && vSecond != NULL){
        Node* first = toNode(vFirst);
        Node* second = toNode(vSecond);

#if MULTI_GRAPH == 0
        for (int k = 0; k < first->adjacencyList->size(first->adjacencyList); k++) {
            if (first->adjacencyList->get(first->adjacencyList, k) == vSecond){
                return;
            }
        }
#endif

        first->adjacencyList->addLast(first->adjacencyList, second);
#if DIRECTED == 0 && SELF_LOOP == 1
        if (i != j){
            second->adjacencyList->addLast(second->adjacencyList, first);
        }
#elif DIRECTED == 0 && SELF_LOOP == 0
        second->adjacencyList->addLast(second->adjacencyList, first);
#endif
    }
}

void* removeNode(void* this, int i){
    LinkedList* list = getList(this);
#if DIRECTED == 0
    Node *removed = list->get(list, i);

    int j = 0;
    while (j < removed->adjacencyList->size(removed->adjacencyList)) {
        Node* adjacentNode = removed->adjacencyList->get(removed->adjacencyList, j);

        int k = 0;
        while (k < adjacentNode->adjacencyList->size(adjacentNode->adjacencyList)){
            if (adjacentNode->adjacencyList->get(adjacentNode->adjacencyList, k) == (void*)removed){
                adjacentNode->adjacencyList->remove(adjacentNode->adjacencyList, k);
#if MULTI_GRAPH == 0
                break;
#endif
            }
            k++;
        }

        j++;
    }
#endif

    return toNode(list->remove(list, i))->object;
}

void removeEdge(void* this, int i, int j){
    LinkedList* list = getList(this);

#if SELF_LOOP == 0
    if (i == j){
        return;
    }
#endif

    void *vFirst = list->get(list, i);
    void *vSecond = list->get(list, j);

    if (vFirst != NULL && vSecond != NULL) {
        Node *first = toNode(vFirst);
        Node *second = toNode(vSecond);

        int k = 0;
        while (k < first->adjacencyList->size(first->adjacencyList)) {
            if (first->adjacencyList->get(first->adjacencyList, k) == vSecond){
                first->adjacencyList->remove(first->adjacencyList, k);
#if MULTI_GRAPH == 0
                break;
#endif
            }
            k++;
        }

#if DIRECTED == 0
        k = 0;
        while (k < second->adjacencyList->size(second->adjacencyList)){
            if (second->adjacencyList->get(second->adjacencyList, k) == vFirst){
                second->adjacencyList->remove(second->adjacencyList, k);
#if MULTI_GRAPH == 0
                break;
#endif
            }
            k++;
        }
#endif
    }
}

Node* getNode(void* this, int i){
    LinkedList* list = getList(this);
    return (Node*)list->get(list, i);
}

Graph *createGraph() {
    Graph* out = malloc(sizeof(Graph) + sizeof(void*));
    void** p_out = (void**)out;
    Private* aPrivate = createPrivate(NUMBER_OF_PRIVATE_FIELDS);
    LinkedList* listOfNodes = createLinkedList();

    aPrivate->privateField[LIST_OF_NODES] = listOfNodes;
    p_out[sizeof(Graph) / 4] = aPrivate;

    out->numberOfNodes = numberOfNodes;
    out->add = addNode;
    out->addEdge = addEdge;
    out->remove = removeNode;
    out->removeEdge = removeEdge;
    out->get = getNode;

    return out;
}
