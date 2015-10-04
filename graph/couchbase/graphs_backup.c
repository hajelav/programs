/**
 * @file: graphs.c
 * @brief: solution to find the maximum path length from the root
 *  	   node to the most distant remote(with and without loops) 
 * @author: Vivek Hajela
 * @date: 2015-10-01
 * @programming language: C
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

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

/**
 * @brief   : this function initilizes the graph. 
 * 	      sets the name of nodes starting from index 0
 * @param g : graph data structure
 * @param n : total number of nodes in the graph
 */
void init_graph(GRAPH *g, uint64_t n){

    uint64_t i;
    if(!g || n<=0){
	perror("Error initilizing graph");
	return;
    }

    for(i=0;i<n;i++){
	g[i].idx = i; 		/*fill the node name starting with index 0*/
	g[i].gnode = NULL;
	g[i].dist = 0;		/*set the dist to zero, initially	  */
    }
}

/**
 * @brief   : Mark all the nodes as un-visited
 * @param g : graph data structure
 * @param n : number of nodes in the graph
 */
void clear_visited_vertex(GRAPH *g, uint64_t n) {
    
    uint64_t i;
    if(!g || !n) {
	perror("Error clearing nodes");
	return;
    }

    for(i=0;i<n;i++){
	g[i].processed = 0;
    }
}

/**
 * @brief     : create a graph node
 * @param idx : index of node
 * @return    : pointer to graph node, NULL on error
 */
GNODE* create_gnode(uint64_t idx) {

    GNODE* gn = (GNODE*)malloc(sizeof(GNODE));
    if(!gn || idx < 0){
	perror("Error creating node.");
	return NULL;
    }

    gn->idx = idx;
    gn->next = NULL;
    return gn;
}

/**
 * @brief     : creates a graph. Its is represented by adjacency list
 * @param g   : pointer to graph
 * @param idx : index of node
 */
void create_graph( GRAPH *g, uint64_t idx) {

    GNODE *gn;  	/*graph node*/
    GNODE *temp;

    if(!g || idx < 0){
	perror("Error creating graph.");
	return;
    }

    gn = create_gnode(idx);
    if(!gn) {
	perror("Error creating graph.malloc failed");
	return;
    }

    /*Add the gnodes to the link list*/
    if(!g->gnode){ 
	g->gnode = gn;
    } else {
	temp = g->gnode;
	g->gnode  = gn;
	gn->next = temp;
    }
}

/*prints the graph adjacency list*/
void print_graph(GRAPH *g, uint64_t n) {
    uint64_t i;
    GNODE *trav;

    if(!g || n <= 0){
	perror("Error printing graph.");
	return;
    }
    for(i=0;i<n;i++){
	trav = g[i].gnode;
	    printf("node[%lu]-->", i);
	while(trav){
	    printf("%lu", trav->idx);
	    trav = trav->next;
	}
	printf("\n");
    }
}

/*print the distance from the root for each node*/
void print_dist(GRAPH *g, uint64_t n) {
    uint64_t i;

    if(!g || n <= 0){
	perror("Error printing distance.");
	return;
    }
    for(i=0;i<n;i++){
	printf("node[%lu] --> distance[%zu]", i, g[i].dist);
	printf("\n");
    }
}

/*check if the node is visited*/
int isVisited(GRAPH *g, uint64_t idx) {
    return(g[idx].processed);
}

/*get the maximum path length */
int get_max_path_len(GRAPH *g, uint64_t n) {

	int max_dist = INT_MIN;
	uint64_t i;

	if(!g || n <= 0)
	    return -1;

    for(i=0;i<n;i++){
	 if(g[i].dist > max_dist)
	     max_dist = g[i].dist;
    }

    return max_dist;

}

void max_path_len_no_loop(GRAPH *g, uint64_t vtx, uint64_t i){

    GNODE *trav;

    if(i > g[vtx].dist)
	g[vtx].dist = i;

    trav = g[vtx].gnode;

    while(trav){
	max_path_len_no_loop(g, trav->idx, i+1);
	trav = trav->next;
    }
}

/**
 * @brief      :  caluculates the max path length from the src node(may contain loops)
 * 	    	  We use a variant of DFS to get the max path. as we move along the nodes 
 * 	    	  in DFS, we mark the nodes as visited(g[vtx].processed) and update the 
 * 	    	  distances for each node(g[vtx].dist) only if the new distance is more 
 * 	    	  than the distance already stored in the node. If the graph does not have
 * 	          loops, then we dont need to keep track of visited nodes as DFS recursion
 * 	          would termiate when there are no more chilren left to be traversed for
 * 	          a node.
 * @param g   : graph data structure
 * @param vtx : node index
 * @param i   : variable used to track the distance in DFS
 */
void max_path_len_loop(GRAPH *g, uint64_t vtx, uint64_t i){

    GNODE *trav;

    if(isVisited(g, vtx)){
	/*if we reach here that means , we have already came to a vertex which is already visited.*/
	return;
    }
    
    if(i > g[vtx].dist)
	g[vtx].dist = i;

    g[vtx].processed = 1;
    trav = g[vtx].gnode;

    while(trav){
	max_path_len_loop(g, trav->idx, i+1);

	trav = trav->next;
    }
	g[vtx].processed = 0;
}

/**
 * @brief     : wrapper to calculate the max path length from the src node(may contain loops)
 * @param g   : graph data structure
 * @param src : source(root) node
 * @param n   : total number of nodes
 * @param c   : with loop or without loop
 */
void max_path_len(GRAPH *g, int src, uint64_t n, char c) {

    GRAPH * root;

    if(!g || (src<0) || (n<=0) || (c == '\0')) {
	perror("input error");
	return;
    }

    /*mark all the vertices as unvisited*/
    clear_visited_vertex(g, n);

    if(!(root = &g[src])) {
	perror("graph not initialized");
	return;
    }

    if(c == 'n')
	max_path_len_no_loop(g, 0, 0);
    else 
	max_path_len_loop(g, 0, 0);
}

int main() {
    char c;
    int choice, i, j,  adj, vtx;
    uint64_t n; /* no of nodes in graph*/
    GRAPH *g;

    do {
	printf("MENU OPTIONS\n");
	printf("1 -- create a graph\n");
	printf("2 -- print graph\n");
	printf("3 -- max path len with no loop\n");
	printf("4 -- max path len with loop\n");

	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){

	    case 1: 
		printf("Enter the number of nodes(vertices) in graph\n");
		scanf("%lu", &n);

		g = (GRAPH*)malloc(sizeof(GRAPH)*n);

		if(!g)
		    perror("malloc failed. cannot init graph");

		init_graph(g, n);
		printf("Enter adjecent nodes\n");
		for(i=0;i<n;i++){
		    printf("Enter no of children nodes to node %d\n", i);
		    scanf("%d", &adj);
		    for(j=0;j<adj;j++){
			printf("enter child node\n");
			scanf("%d", &vtx);
			create_graph(&g[i], vtx);
		    }
		}
		break;
	    case 2:
		print_graph(g, n);
		break;

	    case 3:
		printf("Enter the root node in graph\n");
		scanf("%d", &vtx);
		max_path_len(g, vtx, n, 'n');
		print_dist(g, n);
		break;

	    case 4:
		printf("Enter the root node in graph\n");
		scanf("%d", &vtx);
		max_path_len(g, vtx, n, 'y');
		print_dist(g, n);
		get_max_path_len(g, n);
		break;

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
