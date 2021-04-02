#include <malloc.h>
#include "LinkedList.h"
#include "Private.h"
#include "Container.h"

#define NUMBER_OF_PRIVATE_FIELDS 3
#define SIZE 0
#define FIRST_CONTAINER 1
#define LAST_CONTAINER 2

static Private* getPrivate(void* this){
    void** p_this = (void**)this;
    return (Private*)p_this[sizeof(LinkedList) / 4];
}

static Container* getFirstContainer(void* this){
    Container* out = (Container*)(getPrivate(this)->privateField[FIRST_CONTAINER]);
    return out;
}

static Container* getLastContainer(void* this){
    Container* out = (Container*)(getPrivate(this)->privateField[LAST_CONTAINER]);
    return out;
}

int size(void* this){
    Private* aPrivate = getPrivate(this);
    return *((int*)(aPrivate->privateField[SIZE]));
}

LinkedList *createLinkedList() {
    LinkedList* out = malloc(sizeof(LinkedList) + sizeof(void*));
    Private* aPrivate = createPrivate(NUMBER_OF_PRIVATE_FIELDS);

    Container *first = createEmptyContainer();
    Container *last = createEmptyContainer();
    first->next = last;
    first->previous = last;
    last->next = first;
    last->previous = first;

    aPrivate->privateField[SIZE] = malloc(sizeof(int));
    (*((int*)aPrivate->privateField[SIZE])) = 0;
    aPrivate->privateField[FIRST_CONTAINER] = first;
    aPrivate->privateField[LAST_CONTAINER] = last;

    void** p_out = (void**)out;
    p_out[sizeof(LinkedList) / 4] = (void*)aPrivate;

    out->size = size;

    return out;
}