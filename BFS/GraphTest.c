/********************************************************************************* 
* Alfonso Luis Del Rosario, 1698802
* 2023 Winter CSE101 PA2
* GraphTest.c
*********************************************************************************/
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{
    int n = 6;
    Graph G = newGraph(n);

    printf("Starting Program...\n");

    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 2, 6);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);

    printf("ORDER: %d\n", getOrder(G));
    printGraph(stdout, G);
    
    return 0;
}