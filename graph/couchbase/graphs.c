/**
 * @file: graphs.c
 * @brief: solution to find the maximum path length from the root
 *  	   node to the most distant remote(with and without loops) 
 * @author: Vivek Hajela
 * @date: 2015-10-01
 * @programming language: C
 */

#include "graph_util.h"

/*get the maximum path length */
int get_max_path_len(GRAPH *g, uint64_t n) {

	uint64_t max_dist = 0;
	uint64_t i;

	if(!g || n <= 0)
	    return -1;

    for(i=0;i<n;i++){
	 if(g[i].dist > max_dist)
	     max_dist = g[i].dist;
    }


    return max_dist;
}
/**
 * @brief     : this function to show the logic of finding the max len
 * 	        when the graph dosent have loops. Note that we do not track 
 * 	        the visited nodes for no-loop(Directed acycclic graphs)
 * 	        (NOTE: THIS FUNCTION IS NOT USED)
 *
 * @param g   : graph data structure 
 * @param vtx : node index
 * @param i   : variable used to track distance in DFS(depth first search)
 */
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
 * @brief     : wrapper function to calculate the max path length from the src node(may contain loops)
 * @param g   : graph data structure
 * @param src : source(root) node
 * @param n   : total number of nodes
 * @param c   : with loop or without loop
 */
int max_path_len(GRAPH *g, int src, uint64_t n) {

    GRAPH * root;

    if(!g || (src<0) || (n<=0)) {
	perror("input error");
	return -1;
    }

    /*mark all the vertices as unvisited*/
    clear_visited_vertex(g, n);

    if(!(root = &g[src])) {
	perror("graph not initialized");
	return -1;
    }

	/*max_path_len_no_loop(g, 0, 0);*/
	max_path_len_loop(g, 0, 0);

	return 1;
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
	printf("3 -- max path len with loop\n");

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
		if(max_path_len(g, vtx, n) > 0) {
		    print_dist(g, n);
		    printf("\nMaximum path length : %d\n", get_max_path_len(g, n));

		}
		/*free the mem to avoid mem leak*/
		free_graph(g, n);
		break;

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n");
    }while((c=getchar())!='q'); 
    return 0;
}
