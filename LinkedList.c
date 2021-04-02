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

static int* p_size(void* this){
    Private* aPrivate = getPrivate(this);
    return (int*)(aPrivate->privateField[SIZE]);
}

int size(void* this){
    return *p_size(this);
}

int isEmpty(void* this){
    return size(this) == 0;
}

void addLast(void* this, void* object){
    Container* last = getLastContainer(this);
    int* size = p_size(this);

    Container* newContainer = createContainer(object, last, last->previous);
    last->previous->next = newContainer;
    last->previous = newContainer;
    (*size)++;
}

void add(void* this, void* object, int i){
    Container* first = getFirstContainer(this);
    Container* last = getLastContainer(this);
    int* size = p_size(this);

    Container* cur = first->next;
    int j = 0;
    while (cur != last && j != i){
        cur = cur->next;
    }

    if (cur != last){
        Container* newContainer = createContainer(object, cur, cur->previous);
        cur->previous->next = newContainer;
        cur->previous = newContainer;
        (*size)++;
    }
}

void* removeLast(void* this){
    Container* first = getFirstContainer(this);
    Container* last = getLastContainer(this);
    int* size = p_size(this);

    Container* lastContainer = last->previous;

    if (lastContainer != first){
        lastContainer->previous->next = lastContainer->next;
        lastContainer->next->previous = lastContainer->previous;
        (*size)--;

        void *lastObject = lastContainer->object;
        free(lastContainer);

        return lastObject;
    }

    return NULL;
}

void* remove(void* this, int i){
    Container* first = getFirstContainer(this);
    Container* last = getLastContainer(this);
    int* size = p_size(this);

    Container* cur = first->next;
    int j = 0;
    while (cur != last && j != i){
        cur = cur->next;
    }

    if (cur != last){
        cur->previous->next = cur->next;
        cur->next->previous = cur->previous;
        (*size)--;

        void *lastObject = cur->object;
        free(cur);

        return lastObject;
    }

    return NULL;
}

void* get(void* this, int i){
    Container* first = getFirstContainer(this);
    Container* last = getLastContainer(this);

    Container* cur = first->next;
    int j = 0;
    while (cur != last && j != i){
        cur = cur->next;
    }

    return cur->object;
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
    out->isEmpty = isEmpty;
    out->addLast = addLast;
    out->add = add;
    out->removeLast = removeLast;
    out->remove = remove;
    out->get = get;

    return out;
}