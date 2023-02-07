/********************************************************************************* 
* Alfonso Luis Del Rosario, 1698802
* 2023 Winter CSE101 PA3
* GraphTest.c
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

void print_distances(Graph G, int n);
void print_paths(Graph G, int n);
void print_times(Graph G);
void print_all(Graph G, int source);
void print_discover(Graph G);
void print_finish(Graph G);
void print_parents(Graph G);

int main(int argc, char* argv[])
{
    int g_size = 8;
    
    Graph G = newGraph(g_size);
    Graph G2 = newGraph(g_size);
    Graph Copy = NULL;
    Graph T = NULL;
    List S = newList(); //Stack

    //Stack initialization
    for(int i = 1; i <= getOrder(G); i++)
    {
        append(S, i);
    }

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

    printf("FIELDS AFTER ADDING EDGES\n");
    printf("Adjacency List: \n");
    printGraph(stdout, G);

    printf("\nORDER: %d\n", getOrder(G));
    printf("SOURCE: %d\n", getSource(G));
    printf("SIZE: %d\n", getSize(G));

    printf("========================================\n");
    printf("FIELDS BEFORE ADDING ARCS\n");
    printf("ORDER: %d\n", getOrder(G2));
    printf("SOURCE: %d\n", getSource(G2));
    printf("SIZE: %d\n\n", getSize(G2));

    printf("FIELDS AFTER ADDING ARCS\n");
    addArc(G2, 1, 3);
    addArc(G2, 2, 4);
    addArc(G2, 2, 6);
    addArc(G2, 2, 3);
    addArc(G2, 3, 8);
    addArc(G2, 3, 6);
    addArc(G2, 4, 1);
    addArc(G2, 4, 2);
    addArc(G2, 5, 8);
    addArc(G2, 6, 2);
    addArc(G2, 6, 5);
    addArc(G2, 7, 4);
    addArc(G2, 7, 5);
    addArc(G2, 8, 1);

    printf("Adjacency List\n");
    printGraph(stdout, G2);

    printf("\nORDER: %d\n", getOrder(G2));
    printf("SOURCE: %d\n", getSource(G2));
    printf("SIZE: %d\n", getSize(G2));

    printf("========================================\n");
    
    printf("Adjacency List After Transpose\n");
    T = transpose(G2);
    printGraph(stdout, T);

    printf("\nFIELDS AFTER ADDING TAKING TRANSPOSE\n");
    printf("ORDER: %d\n", getOrder(T));
    printf("SOURCE: %d\n", getSource(T));
    printf("SIZE: %d\n", getSize(T));

    printf("========================================\n");

    print_all(G, 4); //BFS RUN FOR SOURCE 4

    // DFS RUNNING // 

    printf("DFS RUNNING FOR ALL VERTICES IN STACK\n\n");
    printf("Graph being used:\n");
    printGraph(stdout, G2);
    printf("\n");

    printf("Stack Created for DFS Call: ");
    printList(stdout, S);
    printf("\n\n");
    printf("Stack values after DFS call: ");
    DFS(G2, S);
    printList(stdout, S);
    printf("\n\n");

    print_discover(G2);
    printf("\n");
    print_finish(G2);

    printf("========================================\n");

    printf("Check for copyGraph()\n\n");
    
    Copy = copyGraph(G2);

    printf("ORIGINAL DIGRAPH: \n");
    printGraph(stdout, G2);
    printf("\nCOPY OF ORIGINAL DIGRAPH: \n");
    printGraph(stdout, Copy);
    
    printf("========================================\n");
    
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

////////////////////////////////////////////////////////////////////////

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

void print_discover(Graph G)
{
    int i = 1;
    printf("Discover times of all vertices: ... \n");
    while(i <= getOrder(G))
    {
        printf("%d: %d\n", i, getDiscover(G, i));
        i++;
    }
}

void print_finish(Graph G)
{
    int i = 1;
    printf("Finish times of all vertices: ... \n");
    while(i <= getOrder(G))
    {
        printf("%d: %d\n", i, getFinish(G, i));
        i++;
    }
}

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

void print_times(Graph G)
{
    int i = 1;
    printf("Discover times of all vertices: ... \n");
    while(i <= getOrder(G))
    {
        printf("%d: %d\n", i, getDiscover(G, i));
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