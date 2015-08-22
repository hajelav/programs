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
    
} GRAPH;

typedef struct edge {
    int from_vtx;
    int to_vtx;
    int shortest_edge;
} EDGE;

void init_edge(EDGE *g) {

    g->shortest_edge = INT_MAX;
    g->from_vtx = INT_MIN;
    g->to_vtx = INT_MIN;
}

void init_graph(GRAPH *g, int n){

    int i;
    if(!g || !n)
	return;

    for(i=0;i<n;i++){
	g[i].idx = i;
	g[i].torder = 0;
	g[i].gnode = NULL;
    }
}

void clear_visited_vertex(GRAPH *g, int n) {
    
    int i;
    if(!g || !n)
	return;

    for(i=0;i<n;i++){
	g[i].processed = 0;
	g[i].torder = 0;
    }

}

//create graph node
GNODE* create_gnode(int idx, int edge) {

    GNODE* gn = (GNODE*)malloc(sizeof(GNODE));
    if(!gn)
	return NULL;
    gn->idx = idx;
    gn->edge_len = edge;
    gn->next = NULL;
    return gn;

}

void create_graph( GRAPH *g, int idx, int edge) {

    GNODE *gn, *temp;

    gn = create_gnode(idx, edge);
    if(!gn)
	return;
    if(!g->gnode){ 
	g->gnode = gn;
    } else {
	temp = g->gnode;
	g->gnode  = gn;
	gn->next = temp;
    }
}

void print_graph(GRAPH *g, int n) {
    int i;
    GNODE *trav;

    for(i=0;i<n;i++){
	trav = g[i].gnode;
	    printf("%d-->", i);
	while(trav){
	    printf("%d ", trav->idx);
	    trav = trav->next;
	}
	printf("\n");
    }
}

/*
 *get the vertex node(GNODE) with shortest  edge. this routine scans 
 *processed nodes and find the shortest edge out the processed mould
 */

void get_shortest_edge(GRAPH *g, int n, EDGE* e) {

    int i;
    GNODE *trav;
    //create node (shortest vertex)
    GNODE* minv = create_gnode(INT_MAX, INT_MAX);
    if(!g || !minv || !e)
	return;

    for(i=0;i<n;i++){
	
	if(g[i].processed){ //look for the unvisited edges out of processed vertices(mould)

	trav = g[i].gnode;
	    while(trav){

		//while traversing the adjaceny list we only need to look at the vertices which are not
		//visited. Once we have found such an edge, we store the results. When this function returns
		//we have the smallest from--->to edge to be considered from the mould(set of already sucked in vertices)
		//in the MST
		if((!g[trav->idx].processed) && (trav->edge_len <  e->shortest_edge)) {
		    e->shortest_edge = trav->edge_len;
		    e->from_vtx = i;
		    e->to_vtx = trav->idx;
		}
		trav = trav->next;
	    } //while ends
	} //check if node is processed

    } //end for loop

    /*once we have found found the min edge, we mark the 'to' vertex as processed*/
    g[e->to_vtx].processed = 1;
    /*printf("%d ", e->to_vtx);*/
}


int is_all_nodes_processed(GRAPH *g, int n){

    int i;

    for(i=0;i<n;i++){
	if(!g[i].processed)
	    return 1;
    }
    return 0; 
}

//this function returns the new adjacency list for minimum spanning tree  for undirected graphs( note that
//this MST list allocates new memory, which is different than original graph

GRAPH* prims_MST(GRAPH *g, int n){

    GRAPH *mst;
    EDGE e;

    if(!g)
	return NULL;

    mst = (GRAPH*) malloc(sizeof(GRAPH)*n);
    init_graph(mst, n);
    init_edge(&e);

    //mark the first vertex as processed

    g[0].processed = 1;
    while(is_all_nodes_processed(g, n)){

	get_shortest_edge(g, n, &e);
	/*printf("\n%d--(%d)--%d", e.from_vtx, e.shortest_edge, e.to_vtx);*/

	//we have found the new edge to be sucked into mould, now create  new MST
	create_graph(&mst[e.from_vtx], e.to_vtx, e.shortest_edge); 
	create_graph(&mst[e.to_vtx], e.from_vtx, e.shortest_edge); 
	init_edge(&e);
    }
    return mst;
}

int isVisited(GRAPH *g, int idx) {
    return(g[idx].processed);
}

/* DFS */
void DFS(GRAPH *g, int vtx){

    GNODE *trav;

    if(isVisited(g, vtx)){
	/*if we reach here that means , we have already came to a vertex which is already visited.*/
	return;
    }
    
    g[vtx].processed = 1;
    trav = g[vtx].gnode;
    printf("%d->", vtx);

    while(trav){
	DFS(g, trav->idx);
	trav = trav->next;
    }
}

/*
 *variant of DFS: if cycle is found , we store 1 in cycle variable
 */
void DFS_cycle(GRAPH *g, int vtx, int *path, int *cycle) {

    GNODE *trav;
    if(isVisited(g, vtx)){
	/*if we reach here that means , we have already came to a vertex which is already visited.*/
	return;
    }

    g[vtx].processed = 1;

    trav = g[vtx].gnode;
	path[vtx] = 1;
    while(trav){
	if(!path[trav->idx]) {
	    DFS_cycle(g, trav->idx, path, cycle);
	} else {
	    //we have found a vertex we have already visited in a path. hence a cycle
	    *cycle |= 1; 
	}
	trav = trav->next;
    }
    //remove the vertex from the path array , since there was no cycle
	path[vtx] = 0;
}

int  detect_cycle(GRAPH *g, int n) {


    int cycle = 0, i;
    /*
     *path array:if we havent visited a vertex, we add 1 to the corresponding index of the the vertex; eg path[vertex] = 1
     */
    int *path = (int*)malloc(sizeof(int)*n);

    //mark all nodes in the path array as unvisited(0) initially
    for(i=0;i<n;i++){
	path[i] = 0;
    }

    for(i=0;i<n;i++) {
	DFS_cycle(g, i, path, &cycle);
	cycle |= cycle;
	/*printf("Vertex=%d, cycle = %d\n", i,cycle);*/
	/*cycle = 0;*/
    }

    return cycle;
}

//return 0 only when queue is empty , ie when all the element are set to -1
int queue_empty(int *q, int n) {

    int i;
    for(i=0;i<n;i++){
	if(q[i] != -1)
	    return 0;
    }
    return 1;
}

/* BFS  for directed/undirected graphs*/
void BFS(GRAPH *g, int vtx, int n) {

    //create a queue
    int *q, i;
    int head = 1, tail = 0;
    GNODE *trav;

    q  = (int*)malloc(sizeof(int)*n);
    //set all elements of queue to -1
    for(i=0;i<n;i++){
	q[i] = -1;
    }

    // initialize the queue with the start vertex(vtx)
    q[tail] = vtx;

    //mark the start vertex(vtx) as visited
    g[vtx].processed = 1;

    while(!queue_empty(q, n)) {
	
	trav = g[q[tail]].gnode;
	while(trav) {
	    //if the vertices are not visited, then only add to the queue
	    if(!g[trav->idx].processed){
		//add the adject vertices of g[tail] in the queue
		q[head] = trav->idx;
		head++;
		g[trav->idx].processed = 1;
	    }
	    trav = trav->next;
	}
	printf("%d->", q[tail]);
	
	//remove vertex from the queue
	q[tail]  = -1;
	tail++;
    }
    free(q);
}


/*
 *Dijiktra Algorithm : computes single source shortest path for non-negative edge graph
 1. does not work on non negative edge costs
 2. not very distributed, ie not good for applications where the entire graph cannot fit into the main memory(eg internet routing)
 */


/*
 *Bellman-ford algorithm : Computes single source shortest path
 *1. can be used for negative edges
 *2. is distributed in nature
 *3  does not work , if there is a negative cycles in the graph , but will show us the negative cycle
 *4. computes single source shortest path , if there are no negative cycles 
 */

/* 
 * Topological ordering: its an ordering of vertices of a graph such that all of the directed edges only go
 * forward in the ordering. A necessary condition for a graph to have a topological ordering is that it should 
 * be directed acyclic graph (DAG)
 *
 * Implementation : finding topological ordering is just a variant of DFS  */


void print_topological_order(GRAPH *g, int n) {
    int i;

    for(i=0;i<n;i++){
	    printf("vertex = %d--> Topological order = %d\n", i, g[i].torder);
    }
}

void DFS_topological(GRAPH *g, int vtx, int *torder){

    GNODE *trav;

    if(isVisited(g, vtx)){
	/*if we reach here that means , we have already came to a vertex which is already visited.*/
	return;
    }
    
    g[vtx].processed = 1;
    trav = g[vtx].gnode;

    while(trav){
	DFS_topological(g, trav->idx, torder);
	trav = trav->next;
    }
    //assign the topological number and decrement it
    g[vtx].torder = *torder;
    *torder -= 1;
}

void topological_sort(GRAPH *g, int n) {

    int i ,curr_torder;
    //mark all the vertices as unvisited
    clear_visited_vertex(g, n);

    //set the current topological order = no of vertices
    curr_torder = n;

    for(i=0;i<n;i++){
	if(!isVisited(g, i)) {
	    DFS_topological(g, i, &curr_torder);
	}
    }
}

int main() {
    char c;
    int choice, n, i, j,  adj, elen, vtx;
    GRAPH *g;
    do {
	printf("MENU OPTIONS\n");
	printf("1 -- create a graph\n");
	printf("2 -- print graph\n");
	printf("3 -- Prims minimum spanning tree(MST)\n");
	printf("4 -- BFS\n");
	printf("5 -- DFS in a graph\n");
	printf("6 -- Detect cycle in a directed graph\n");
	printf("7 -- Topological sorting\n");
	printf("8 -- Kruskal's MST\n");
	printf("9 -- Print all paths from source to destination\n");

	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){

	    case 1: 
		printf("Enter the number of vertices in graph\n");
		scanf("%d", &n);

		g = (GRAPH*)malloc(sizeof(GRAPH)*n);
		init_graph(g, n);
		printf("Enter adjecency nodes\n");
		for(i=0;i<n;i++){
		    printf("Enter no of adject nodes to vertex %d\n", i);
		    scanf("%d", &adj);
		    for(j=0;j<adj;j++){
			printf("enter edge len and vertex\n");
			scanf("%d %d", &elen, &vtx);
			create_graph(&g[i], vtx, elen);
		    }
		}
		break;
	    case 2:
		print_graph(g, n);
		break;

	    case 3:
		break;

	    case 4:
		break;
		
	    case 5:
		break;

	    case 6:
		break;

	    case 7:
		topological_sort(g, n);
		print_topological_order(g, n);
		break;


	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}

