/********************************************************************************* 
* Alfonso Luis Del Rosario, 1698802
* 2023 Winter CSE101 PA2
* FindPath.c
*********************************************************************************/

#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        fprintf( stderr, "ERROR: MUST PASS TWO ARGUMENTS\n");
        return -1;
    }

    //---------------------------OPENING FILE ARGUMENTS--------------------------------------//

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
    List L = newList();

    //------------ADDS GRAPH EDGES------------//
    while(true)
    {
        int x = 0, y = 0;
        fscanf(file, "%d %d", &x, &y);
        if(x == 0 || y == 0)
            break;
        addEdge(G, x, y);
    }

    printGraph(write, G);
    fprintf(write, "\n");

    //------------RUNNING BFS FOR DISTANCES------------//
    while(true)
    {
        int x = 0, y = 0;
        fscanf(file, "%d %d", &x, &y);
        if(x == 0 || y == 0)
            break;
        clear(L);
        BFS(G, x);

        if(getDist(G , y) == -1)
        {
            fprintf(write, "The distance from %d to %d is infinity\n", x, y);
            fprintf(write, "No %d-%d path exists\n", x, y);
            fprintf(write, "\n");
        }
        else
        {
            fprintf(write, "The distance from %d to %d is %d\n", x, y, getDist(G, y));
            getPath(L, G, y);
            fprintf(write, "A shortest %d-%d path is: ", x, y);
            printList(write, L);
            fprintf(write, "\n\n");
        }
    }

    freeGraph(&G);
    freeList(&L);
    fclose(file);
    fclose(write);

    return 0;
}