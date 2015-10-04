#ifndef	_GRAPH_UTIL_H_
#define	_GRAPH_UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>

/* graphs data structures and APIs*/

/*graph node*/
typedef struct gnode {
    uint64_t idx;		/*node name		*/
    struct gnode *next;		/*link list of children	*/
} GNODE;

/*adjacency list for graph data structure. */
typedef struct graph {
    uint64_t idx; 		/*index of vertex node			*/
    GNODE *gnode;		/*adjacency list for each node		*/
    size_t dist;		/*stores the distance from the root	*/
    int  processed:1;   	/*check if visited. 			*/
} GRAPH;

/* function definitions*/
void init_graph(GRAPH *g, uint64_t n);
void clear_visited_vertex(GRAPH *g, uint64_t n);
GNODE* create_gnode(uint64_t idx);
void create_graph( GRAPH *g, uint64_t idx);
void print_graph(GRAPH *g, uint64_t n);
void print_dist(GRAPH *g, uint64_t n);
int isVisited(GRAPH *g, uint64_t idx);
void free_graph(GRAPH *g, uint64_t n);
int read_graph(GRAPH *g, char *file_name, uint64_t n);

#endif /*  _GRAPH_UTIL_H_ */ 
