/********************************************************************************* 
* Alfonso Luis Del Rosario, 1698802
* 2023 Winter CSE101 PA2
* Graph.h
*********************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#define INF -1
#define NIL -10

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

typedef int GraphElement;
typedef struct GraphObj* Graph;

/***------------------------- Constructors-Destructors -------------------------***/
Graph newGraph(int n); 
//Function newGraph() returns a Graph pointing to a newly 
//created GraphObj representing a graph having n vertices 
//and no edges.

void freeGraph(Graph* pG);
//Function freeGraph() frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL.

/***------------------------- Access functions -------------------------***/
int getOrder(Graph G); // Function getOrder() returns the field order

int getSize(Graph G); // Function getSize() returns the field size

int getSource(Graph G); //  getSource() returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called.

// NOTES:
// Functions getParent(), getDist() and getPath() all have the
// precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).

int getParent(Graph G, int u); 

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

void DFS(Graph G, List S);

Graph transpose(Graph G);

Graph copyGraph(Graph G);

//Function getParent() will return the parent of vertex u in 
//the BFS tree created by BFS(), or NIL if BFS() has not yet been called.

int getDist(Graph G, int u); 
//Function getDist() returns the distance from the most recent BFS 
//source to vertex u, or INF if BFS() has not yet been called. 

void getPath(List L, Graph G, int u); 
// Function getPath() appends to the List L the vertices of a shortest path 
// in G from source to u, or appends to L the value NIL if no such path exists.
// getPath() has the precondition getSource(G)!=NIL, so BFS() must be 
// called before getPath() is called. 

/***------------------------- Manipulation procedures -------------------------***/
void makeNull(Graph G); 
// Function makeNull() deletes all edges of G, 
// restoring it to its original (no edge) state. 

//NOTES: 
//Both addEdge() and addArc() have the precondition 
//that their two int arguments must lie
//in the range 1 to getOrder(G).

void addEdge(Graph G, int u, int v); 
// Function addEdge() inserts a new edge joining u to v, i.e. 
// u is added to the adjacency List of v, and v to the adjacency List of u. 
// Your program is required to maintain these lists in 
// sorted order by increasing labels

void addArc(Graph G, int u, int v); 
// Function addArc() inserts a new directed edge from u to v, i.e. v 
//is added to the adjacency List of u (but not u to the adjacency List of v).

void BFS(Graph G, int s); 
// Function BFS() runs the BFS algorithm on the Graph G with source s,
// setting the color, distance, parent, and source fields of G accordingly 

/***------------------------- Other operations -------------------------***/
void printGraph(FILE* out, Graph G);
//function printGraph() prints the adjacency list 
//representation of G to the file pointed to by out. 
//The format of this representation
//should match the above examples, so all that is 
//required by the client is a single call to printGraph().

#endif