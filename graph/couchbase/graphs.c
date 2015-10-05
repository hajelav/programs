/**
 * @file: graphs.c
 * @brief: solution to find the maximum path length from the root
 *  	   node to the most distant remote(with and without loops) 
 * @author: Vivek Hajela
 * @date: 2015-10-01
 * @programming language: C
 */

/* header file for graph utility */
#include "graph_util.h"

/*get the maximum path length */
int get_max_path_len(GRAPH *g, uint64_t n) {

    uint64_t max_dist = 0;
    uint64_t i;

    if(!g || n == 0)
	return -1;
    /*iterate through all the nodes, and find out the max distance stored*/
    for(i=0;i<n;i++){
	if(g[i].dist > max_dist)
	    max_dist = g[i].dist;
    }
    return max_dist;
}

/**
 * @brief     : this function is to show the logic of finding the max path len
 * 	        when the graph dosent have loops. Note that we do not track 
 * 	        the visited nodes for no-loop graphs(Directed acycylic graphs)
 * 	        (NOTE: THIS FUNCTION IS NOT USED)
 *
 * @param g   : graph data structure 
 * @param vtx : node index
 * @param i   : recursion variable used to track distance in DFS(depth first search)
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
 * @brief      	     : calculates the max path length from the src node(may contain loops)
 * 	    	       We use a variant of DFS to get the max path. As we move along the nodes 
 * 	    	       in DFS, we mark the nodes as visited(g[vtx].processed) and update the 
 * 	    	       distances for each node(g[vtx].dist) using a variable(i), only if the new
 * 	    	       distance is more than the distance already stored in the node. If the graph 
 * 	    	       does not have loops, then we dont need to keep track of visited nodes as DFS
 * 	    	       recursion would termiate when there are no more chilren left to be traversed for
 * 	               a node.However when the graph has loops the recursive call would return whenever
 * 	               a previously visited node is encountered. 
 * @param g          : graph data structure
 * @param vtx 	     : node index
 * @param path_len   : distance of node from the source node
 */
void max_path_len_loop(GRAPH *g, uint64_t vtx, uint64_t path_len){

    GNODE *trav;

    if(isVisited(g, vtx)){
	/*if we reach here that means , we have came to a node which is already visited.*/
	return;
    }

    /*update the distance only if its is more than previously stored distance*/
    if(path_len > g[vtx].dist)
	g[vtx].dist = path_len;

    /*once we visted a node, we mark it as visited*/
    g[vtx].processed = 1;

    /*get the neighbors(children) of the node*/
    trav = g[vtx].gnode;

    /*traverse the child nodes recursively*/
    while(trav){
	max_path_len_loop(g, trav->idx, path_len+1);
	trav = trav->next;
    }

    /*once we update the distance, we mark nodes as unvisited, so that distances can be updated again*/
    g[vtx].processed = 0;
}

/**
 * @brief     : wrapper function to calculate the max path length from the src node(may contain loops)
 * @param g   : graph data structure
 * @param src : source(root) node
 * @param n   : total number of nodes
 */
int max_path_len(GRAPH *g, int src, uint64_t n) {

    GRAPH * root;

    if(!g || (src<0) || (n==0)) {
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
	max_path_len_loop(g, src, 0);

	return 1;
}

int main (int argc, char *argv[]) {
    int  vtx;
    uint64_t n; /* no of nodes in graph*/
    GRAPH *g;

    if(argc < 3){
	printf("Incorrect number of arguments\n");
	printf("Usage : ./graphs <no of nodes> <input txt file>\n");
	exit(0);
    }

    /*get the number of nodes from the program*/
    n = atoi(argv[1]);

    g = (GRAPH*)malloc(sizeof(GRAPH)*n);

    if(!g)
	perror("malloc failed. cannot init graph");

    init_graph(g, n);

    if(read_graph(g, argv[2], n) > 0) {

	if(g && n > 0)
	    print_graph(g, n);

	printf("Enter the root node in graph\n");
	scanf("%d", &vtx);

	if(max_path_len(g, vtx, n) > 0) {
	    print_dist(g, n);
	    printf("\nMaximum path length : %d\n", get_max_path_len(g, n));
	}
    }

    /*free the mem to avoid mem leak*/
    free_graph(g, n);
    return 0;
}
