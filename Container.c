#include <malloc.h>
#include "Container.h"

Container *createEmptyContainer() {
    Container *out = malloc(sizeof(Container));

    out->object = NULL;
    out->next = NULL;
    out->previous = NULL;

    return out;
}

Container *createContainer(void *object, Container *next, Container *previous) {
    Container *out = malloc(sizeof(Container));

    out->object = object;
    out->next = next;
    out->previous = previous;

    return out;
}