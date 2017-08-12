#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* graphs data structures */

//graph node
typedef struct gnode {
    int idx;
    int edge_len;
    struct gnode *next;
} GNODE;

//graph vertex
typedef struct graph {
    int idx; //index of vertex node
    GNODE *gnode;
    int torder; // topological order of the vertex
    unsigned int processed:1; //visited
    int dist;
} GRAPH;

typedef struct edge {
    int from_vtx;
    int to_vtx;
    int shortest_edge;
} EDGE;

void init_edge(EDGE *g);
void init_graph(GRAPH *g, int n);
void clear_visited_vertex(GRAPH *g, int n);
//create graph node
GNODE* create_gnode(int idx, int edge);
void create_graph( GRAPH *g, int idx, int edge);
void print_graph(GRAPH *g, int n);
int is_all_nodes_processed(GRAPH *g, int n);
int isVisited(GRAPH *g, int idx);
