/********************************************************************************* 
* Alfonso Luis Del Rosario, 1698802
* 2023 Winter CSE101 PA2
* GraphTest.c
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

void print_distances(Graph G, int n)
{
    int i = 1;
    printf("Distance from %d to: ... \n", n);
    while(i <= getOrder(G))
    {
        printf("%d: %d\n", i, getDist(G, i));
        i++;
    }
}

void print_paths(Graph G, int n)
{
    List L = newList();
    int i = 1;

    printf("All paths from %d to: ... \n", n);
    while(i <= getOrder(G))
    {
        printf("%d: ", i);
        getPath(L, G, i);
        printList(stdout, L);
        clear(L);
        printf("\n");
        i++;
    }

    freeList(&L);
}

void print_parents(Graph G)
{
    int i = 1;
    printf("Parents of vertices: ... \n");
    while(i <= getOrder(G))
    {
        printf("%d: %d\n", i, getParent(G, i));
        i++;
    }
}

void print_all(Graph G, int source)
{
    printf("========================================\n");


    BFS(G, source);
    printf("BFS RUNNING FOR VERTEX %d\n\n", getSource(G));
    
    print_distances(G, getSource(G));
    printf("\n");
    print_paths(G, getSource(G));
    printf("\n");
    print_parents(G);

    printf("========================================\n");
}

int main(int argc, char* argv[])
{
    int g_size = 8;
    
    Graph G = newGraph(g_size);

    printf("========================================\n");
    printf("GRAPH TEST PROGRAM STARTING...\n\n");

    printf("FIELDS BEFORE ADDING EDGES\n");
    printf("ORDER: %d\n", getOrder(G));
    printf("SOURCE: %d\n", getSource(G));
    printf("SIZE: %d\n\n", getSize(G));

    addEdge(G, 1, 5);
    addEdge(G, 1, 4);
    addEdge(G, 1, 6);
    addEdge(G, 1, 7);
    addEdge(G, 2, 3);
    addEdge(G, 2, 5);
    addEdge(G, 2, 8);
    addEdge(G, 3, 7);
    addEdge(G, 3, 8);
    addEdge(G, 4, 7);
    addEdge(G, 4, 6);
    addEdge(G, 5, 7);
    addEdge(G, 6, 8);
    addEdge(G, 7, 8);

    printf("Adjacency List: \n");
    printGraph(stdout, G);

    printf("\nFIELDS AFTER ADDING EDGES\n");
    printf("ORDER: %d\n", getOrder(G));
    printf("SOURCE: %d\n", getSource(G));
    printf("SIZE: %d\n", getSize(G));

    print_all(G, 4);
    print_all(G, 6);

    makeNull(G);
    printf("FIELDS AFTER CALLING MAKE NULL\n");
    printf("ORDER: %d\n", getOrder(G));
    printf("SOURCE: %d\n", getSource(G));
    printf("SIZE: %d\n\n", getSize(G));

    printf("ADJACENCY LIST AFTER MAKE NULL\n");
    printGraph(stdout, G);

    freeGraph(&G);
    printf("\n");

    printf("Attempting to print graph after freeGraph(): \n");
    printGraph(stdout, G);

    return 0;
}