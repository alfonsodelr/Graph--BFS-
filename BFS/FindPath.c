
#include "Graph.h"
#include "List.h"

#define MAX_CHAR_LENGTH 20

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
    
    char* vert_count = calloc(MAX_CHAR_LENGTH, sizeof(char));
    fgets(vert_count, MAX_CHAR_LENGTH, file);
    int var = (int)(vert_count[0])-48;

    Graph G = newGraph(var);
    List L = newList();
    char* line = calloc(MAX_CHAR_LENGTH, sizeof(char));

    //------------ADDS GRAPH EDGES------------//
    while(true)
    {
        fgets(line, MAX_CHAR_LENGTH, file);
        if(line[0] == '0' || line[2] == '0')
            break;
        int x = (int)(line[0]) - 48;
        int y = (int)(line[2]) - 48;
        addEdge(G, x, y);
    }

    printGraph(write, G);
    fprintf(write, "\n");

    //------------RUNNING BFS FOR DISTANCES------------//
    while(true)
    {
        fgets(line, MAX_CHAR_LENGTH, file);
        if(line[0] == '0' || line[2] == '0')
            break;
        int x = (int)(line[0]) - 48;
        int y = (int)(line[2]) - 48;
        clear(L);
        BFS(G, x);
        fprintf(write, "The distance from %d to %d is %d\n", x, y, getDist(G, y));
        getPath(L, G, y);
        fprintf(write, "The shortest path from %d-%d is: ", x, y);
        printList(write, L);
        fprintf(write, "\n");
    }

    return 0;
}

/*
QUESTIONS:

Do we kill program for when getDist or getParent is called and BFS isn't run or continue but do nothing with error statement

Should I terminate program for out of bounds error with for example add Edge when 1 <= u <= Order

I implemented everything from index 0 of my list array. Should I redo it or is it fine as long as it works.

Should sourceVertex be NIL by default

Should sourceVertex be set back to NIL when an invalid source is called with BFS

Clearing list inside getpath would case fails in the model graph test. 

Will there be a case where two vertices point to each other in a directed graph. Two arcEdges pointing back and forth? 
if so would that count as two 

what should be the default values of the main fiels:
parent
distance
color
sourceVertex
should I be setting these defaults in newGraph()

if you call bfs on a valid vertex then call it on an invalid vertex should it be set to nil or left as the previous valid vert.

*/