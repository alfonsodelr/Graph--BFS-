/********************************************************************************* 
* Alfonso Luis Del Rosario, 1698802
* 2023 Winter CSE101 PA3
* FindComponents.c
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        fprintf( stderr, "ERROR: MUST PASS TWO ARGUMENTS\n");
        return -1;
    }

    //------------------OPENING FILE ARGUMENTS---------------------//

    FILE* file = fopen(argv[1], "r");
    FILE* write = fopen(argv[2], "w");

    if(file == NULL)
    {
        fprintf(stderr, "File Error: Failed to open %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(write == NULL)
    {
        fprintf(stderr, "File Error: Failed to open %s", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    int var = 0;
    fscanf(file, "%d ", &var);

    Graph G = newGraph(var);
    Graph T = NULL; //Transpose Graph
    List S = newList(); //Stack List

    //------------ADDS GRAPH DIRECTED EDGES------------//
    
    while(true)
    {
        int x = 0, y = 0;
        fscanf(file, "%d %d", &x, &y);
        if(x == 0 || y == 0)
            break;
        addArc(G, x, y);
    }

    for(int i = 1; i <= getOrder(G); i++) //sets S to 1,2,3,...,n 
        append(S, i);

    fprintf(write, "Adjacency list representation of G:\n");
    printGraph(write, G);
    fprintf(write, "\n");

    //------------RUNNING ALGORITHM FOR STRONG COMPONENTS------------//
    DFS(G, S);
    T = transpose(G);
    DFS(T, S);

    //------------PARSING STRONG COMPONENT STACK------------//
    List temp = newList();
    int count = 0;

    for(moveBack(S); index(S) >= 0; movePrev(S))
        if(getParent(T, get(S)) == NIL)
            count++;

    fprintf(write, "G contains %d strongly connected components:\n", count);

    count = 1;
    for(moveBack(S); index(S) >= 0; movePrev(S))
    {
        prepend(temp, get(S));
        if(getParent(T, get(S)) == NIL)
        {
            fprintf(write, "Component %d: ", count++);
            printList(write, temp);
            fprintf(write,"\n");
            clear(temp);
        }
    }

    //------------FREEING ALL MEMORY ALLOCATIONS------------//

    freeList(&temp);
    freeList(&S);
    freeGraph(&T);
    freeGraph(&G);
    fclose(file);
    fclose(write);

    return 0;
}