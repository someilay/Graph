#include <malloc.h>
#include "LinkedList.h"
#include "Private.h"
#include "Container.h"

#define NUMBER_OF_PRIVATE_FIELDS 3
#define SIZE 0
#define FIRST_CONTAINER 1
#define SECOND_CONTAINER 2

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
    aPrivate->privateField[FIRST_CONTAINER] = first;
    aPrivate->privateField[SECOND_CONTAINER] = last;

    return out;
}