#include "LinkedListTest.h"

#if LINKED_LIST_TEST == 1
#include <malloc.h>
#include <stdio.h>
#include "time.h"
#include "LinkedList.h"

const int MAX_SIZE = 50;
const int MIN_SIZE = 5;

const int MAX_VALUE = 100;
const int MIN_VALUE = -100;

void* boxing(int value){
    void* out = malloc(sizeof(int));
    (*((int*)out)) = value;
    return out;
}

int unboxing(void* box){
    return *((int*)box);
}

void printList(LinkedList* list){
    for (int i = 0; i < list->size(list); i++) {
        printf("%d ", unboxing(list->get(list, i)));
    }
    printf("\n");
}

void testLinkedList() {
    srand(time(NULL));

    int size = rand() % (MAX_SIZE - MIN_SIZE + 1) + MIN_SIZE;
    LinkedList* list = createLinkedList();

    printf("Start of test...\n");
    printf("Size of list: %d\n", size);
    printf("Adding to the list:\n");

    for (int i = 0; i < size; i++) {
        int value = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
        if (rand() % 2 || i == 0){
            printf("Adding %d to the end of the list: ", value);
            list->addLast(list, boxing(value));
        } else{
            int index = rand() % list->size(list);
            printf("Adding %d to the %d-th position of the list: ", value, index);
            list->add(list, boxing(value), index);
        }
        printList(list);
    }

    printf("\nRemove element form the list\n\n");

    while (!list->isEmpty(list)){
        if (rand() % 2){
            printf("%d removed from the end of the list: ", unboxing(list->removeLast(list)));
        } else{
            int index = rand() % list->size(list);
            printf("%d removed from the %d-th position of the list: ", unboxing(list->remove(list, index)));
        }
        printList(list);
    }

    printf("\nEnd of tess...\n");
    destroyLinkedList(list, free);
}

#endif