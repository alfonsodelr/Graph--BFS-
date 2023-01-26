
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

    //------------RUNNING BFS FOR DISTANCES------------//
    while(true)
    {
        fgets(line, MAX_CHAR_LENGTH, file);
        if(line[0] == '0' || line[2] == '0')
            break;
        int x = (int)(line[0]) - 48;
        int y = (int)(line[2]) - 48;
        printf("%d %d\n", x, y);
    }





    printf("PRINTING GRAPH\n");
    printGraph(stdout, G);

    return 0;
}