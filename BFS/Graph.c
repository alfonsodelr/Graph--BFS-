/********************************************************************************* 
* Alfonso Luis Del Rosario, 1698802
* 2023 Winter CSE101 PA2
* Graph.c
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <Graph.h>
#include "List.h"

#define INF -1
#define NIL -10

#define NULL_ERROR(x) printf("Graph Error: calling %s() on NULL Graph reference\n", x)
#define EXIT exit(EXIT_FAILURE);

enum color{
    WHITE = 0, BLACK, GRAY
};

typedef struct GraphObj{
    List* list; //double pointer for list of lists.
    int* color;
    int* parent;
    int* distance; 
    int sourceVertex;
    int order; //number of vertices 
    int size; //number of edges
}GraphObj;

Graph newGraph(int n)
{
    Graph G = malloc(sizeof(GraphObj));
    assert(G!=NULL);
    G->list = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int)); //should i set all = NIL?
    G->distance = calloc(n+1, sizeof(int)); 
    G->sourceVertex = 0;
    G->order = 0;
    G->size = 0;

    return G;
}

void freeGraph(Graph* pG)
{
    if(*pG == NULL)
    {
        NULL_ERROR("freeGraph");
        EXIT;   
    }
    
    if(pG != NULL && *pG != NULL)
    {
        //delete everything
    }
}

/*** Access functions ***/

int getOrder(Graph G)
{
    if(G == NULL)
    {
        NULL_ERROR("getOrder");
        EXIT;
    }

    return G->order;
}

int getSize(Graph G)
{
    if(G == NULL)
    {
        NULL_ERROR("getSize");
        EXIT;
    }

    return G->size; 
}

int getSource(Graph G)
{
    if(G == NULL)
    {
        NULL_ERROR("getSource");
        EXIT;
    }

    return G->sourceVertex;
}

int getParent(Graph G, int u)
{
    if(G == NULL)
    {
        NULL_ERROR("getDist");
        EXIT;
    }

    return G->parent[u];
}

int getDist(Graph G, int u)
{
    if(G == NULL)
    {
        NULL_ERROR("getDist");
        EXIT;
    }

    if(u < 1 || u > G->order)
    {
        return INF;
    }

    return G->distance[u];
}

void getPath(List L, Graph G, int u)
{
    if(G == NULL || L == NULL)
    {
        NULL_ERROR("getPath");
        EXIT;
    }

    if(getSource==NIL)
    {
        append(L, NIL);
        return;        
    }

    int current = u;

    while(current != getSource(G))
    {
        prepend(L, getParent(G, current));
        u = getParent(G, current);
    }
}

/*** Manipulation procedures ***/

void makeNull(Graph G)
{
    if (G == NULL)
    {
        NULL_ERROR("makeNull");
        EXIT;
    }

    int i = 0;

    while(i < getSize(G))
    {
        clear(G->list[i]); 
        G->color[i] = WHITE;
        G->parent[i] = 0;
        G->distance[i] = 0;
        i++;
    }

    G->size = 0;
    G->order = 0;
    G->sourceVertex = 0;
}

void addEdge(Graph G, int u, int v) //changes if adj lists are indexed at 0
{
    if(G==NULL)
    {
        NULL_ERROR("addEdge");
        EXIT;
    }

    List U = G->list[u-1];
    List V = G->list[v-1];

    moveFront(U);
    moveFront(V);

    //inserting v to U
    while(v > get(U))
        moveNext(U);
    insertBefore(v,U);
    
    //inserting u to V
    while(u > get(V))
        moveNext(V);
    insertBefore(U,v);

}

void addArc(Graph G, int u, int v)
{
    if(G==NULL)
    {
        NULL_ERROR("addArc");
        EXIT;
    }

    if(u < 1 || u > getOrder(G))
    {
        //BOUND_ERROR
    }

    if(v < 1 || v > getOrder(G))
    {
        //BOUND_ERROR
    }
    List V = G->list[v];

    moveFront(V);

    // inserts u to V and NOT vice versa
    while(u > get(V))
        moveNext(V);
    insertBefore(V, u);

}

void BFS(Graph G, int s)
{
    //sets all elements to undiscovered
    for(int i = 0; i < getSize(G); i++)
    {
        G->color[i] = WHITE;
        G->distance[i] = 0;
        G->parent[i] = NIL;
    }
    //sets source vertex to discovered
    G->distance[s] = 0;
    G->color[s] = GRAY;
    G->parent[s] = NIL;

    int curr = 0;

    List L = newList();
    prepend(L, s);
    while(L != NULL)
    {
        moveFront(L);
        curr = get(L)-1;
        deleteFront(L);
        List temp = G->list[curr];
        moveFront(temp);
        while(temp != NULL)
        {
            int adj_index = get(temp)-1;
            if(G->color[adj_index] == WHITE)
            {
                G->color[adj_index] = GRAY;
                G->distance[adj_index] = G->distance[curr]+1;
                G->parent[adj_index] = curr;
                append(L, adj_index);
                moveNext(temp);
            }
        }
        G->color[curr] = BLACK;
    }
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G)
{

}