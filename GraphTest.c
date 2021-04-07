#include "GraphTest.h"

#if GRAPH_TEST == 1
#include "Graph.h"
#include <malloc.h>
#include <stdio.h>
#include <time.h>

static void* boxing(int value){
    void* out = malloc(sizeof(int));
    (*((int*)out)) = value;
    return out;
}

static int unboxing(void* box){
    return *((int*)box);
}

static void printList(LinkedList* list){
    for (int i = 0; i < list->size(list); i++) {
        printf("%d ", unboxing(((Node*)list->get(list, i))->object));
    }
    printf("\n");
}

static void printGraph(Graph* graph){
    int size = graph->numberOfNodes(graph);
    for (int i = 0; i < size; i++) {
        printf("Node %d with value %d: ", i, unboxing(graph->get(graph, i)->object));
        printList(graph->get(graph, i)->adjacencyList);
    }
}

static const int MAX_SIZE = 15;
static const int MIN_SIZE = 5;

void testGraph(){
    Graph* graph = createGraph();
    LinkedList* listOfNumbers = createLinkedList();
    printf("Start testing...\n");
    printf("Adding nodes...\n");

    srand(time(NULL));
    int size = rand() % (MAX_SIZE - MIN_SIZE + 1) + MIN_SIZE;
    printf("Number of nodes: %d\n\n", size);

    for (int i = 0; i < size; i++) {
        listOfNumbers->addLast(listOfNumbers, boxing(i));
    }

    for (int i = 0; i < size; i++) {
        int index = rand() % listOfNumbers->size(listOfNumbers);
        int value = unboxing(listOfNumbers->get(listOfNumbers, index));
        printf("%d added to graph\n", value);
        graph->add(graph, boxing(value));
        printGraph(graph);
        listOfNumbers->remove(listOfNumbers, index);
    }

    destroyLinkedList(listOfNumbers, free);

    int number_of_edges = rand() % (size * (size - 1) / 2) + 1;
    printf("\nNumber of edges: %d\n\n", number_of_edges);

    for (int i = 0; i < number_of_edges; i++) {
        int first = rand() % size;
        int second = rand() % size;
        printf("Try to add edge between %dth and %dth nodes\n", first, second);
        graph->addEdge(graph, first, second);
        printGraph(graph);
    }

    int number_of_removed_edges = rand() % number_of_edges + 1;
    printf("\nNumber of removed edges %d\n\n", number_of_removed_edges);

    for (int i = 0; i < number_of_removed_edges; i++) {
        int first = rand() % size;
        int second = rand() % size;
        printf("Try to remove edge between %dth and %dth nodes\n", first, second);
        graph->removeEdge(graph, first, second);
        printGraph(graph);
    }

    int number_of_removed_nodes = rand() % size + 1;
    printf("\nNumber of removed nodes %d\n\n", number_of_removed_nodes);

    for (int i = 0; i < number_of_removed_nodes; i++) {
        int index = rand() % graph->numberOfNodes(graph);
        printf("Node %dth is removed\n", index);
        graph->remove(graph, index);
        printGraph(graph);
    }

    printf("\nTest ended...\n");
}

#endif