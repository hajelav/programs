#include "graph.h"
#include "../utils.h"


/******************************************************************************************
GRAPH PROBLEMS AND CONCEPTS
http://www.geeksforgeeks.org/graph-data-structure-and-algorithms/
******************************************************************************************/

void DFS_clone(GRAPH* g, int vtx, GRAPH* gclone){

    GNODE *trav;

    if(isVisited(g, vtx)){
	/*if we reach here that means , we have already came to a vertex which is already visited.*/
	return;
    }

    g[vtx].processed = 1;
    trav = g[vtx].gnode;

    //create a new graph
    /*if(trav)*/

    /*printf("%d->", vtx);*/

    while(trav){
	create_graph(&gclone[vtx], trav->idx, 1);
	DFS_clone(g, trav->idx, gclone);
	trav = trav->next;
    }
}

/* DFS : O(V+E) */
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

	//go through the neighbors
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

/*
 *BFS  for directed/undirected graphs
 *Note : BFS can also be used to compute the shortest path from  a single source to all destinations, when all 
 *edge lenghts of a graph are equal(say 1). This property is used to solve snake and ladder problem(http://www.geeksforgeeks.org/snake-ladder-problem-2/)
 */

void enqueue(GRAPH** q, GRAPH* g, int front, int *end) {
    GNODE *trav;

    if(q[front] == NULL)
	return;

    //get the neigbor vertices of q[front]
    trav = q[front]->gnode;

    while(trav){
	/*insert into the q only if the vertex is not visited*/
	if(!g[trav->idx].processed){
	    q[*end] = &g[trav->idx];
	    //update the distance
	    q[*end]->dist = q[front]->dist + 1;
	    (*end)++;
	    g[trav->idx].processed = 1;
	}
	trav = trav->next;
    }
}

void dequeue(GRAPH **q, int *front) {
    if(q[*front]){
	q[*front] = NULL;
	(*front)++;
    }
}

/*
 *implementation of BFS in graphs using queue, given a source node and number of nodes in a graph
 */
void BFS( GRAPH *g, int src, int n) {

    int front = 0, end; 
    GRAPH **q;

    //create a queue of n(no of vertices) pointers to the the graph nodes
    q  = (GRAPH**)malloc(sizeof(GRAPH*)*n);

    //initialize the queue with source vertex
    q[0] =  &g[src];
    //intitalize front to 0(queue is deleted from front)
    front = 0;
    //intitalize end to front+1(queue is inserted)
    end = front + 1;

    while(front!=end) {
	//insert the neighbors from the end of queue
	enqueue(q, g, front, &end);

	//print from the front and dequeue 
	printf("%d-->", q[front]->idx);

	//delete from the front
	dequeue(q, &front);
    }
}

/*
 *this problem is just a variant of BFS, where we store an extra parameter(distance) at each node. After the BFS is complete
 *the distance parameter at each vertex is the shortest distance from the source vertex
 */

void single_source_shortest_path(){

    /*this program is exactly same as BFS. we are just updating the distances in the enqueue routing*/
}

void print_shortest_dist(GRAPH *g, int n) {
    int i;

    for(i=0;i<n;i++){
	    printf("%d-->  %d", i, g[i].dist);
	printf("\n");
    }
}

/*
 *Dijiktra Algorithm : computes single source shortest path for non-negative edge graph
 1. does not work on negative edge costs
 2. not very distributed, ie not good for applications where the entire graph cannot fit into the main memory(eg internet routing)
 3. Dijikra algo is used when the edge lengths are different
 */


/*
 *Bellman-ford algorithm : Computes single source shortest path
 *1. can be used for negative edges (but should not include -ve cycles as finding shortest path in graphs having -ve cycles is NP hard problem)
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



/*
 *meuseum problem: http://www.careercup.com/question?id=5630807089610752
 *this can be solved running BFS (ie using the variant of BFS where we use BFS to find single source shortest path.
 *refer to single_source_shortest_path())
 *we run BFS from each guard position,  and update the distance in the array only if the new distance is less than the old one
 */


/*
 *inorder traversal using stack
 * Algo:
 *
 * inorder_stack(TREE * root) {
 * 
 * TREE * node;
 * node = root;
 * //create a stack 
 *  S = malloc(...);
 *
 * //push the root in the stack
 * push(node);
 *
 * while(!stack_empty(S)) {
 * //check if node left is not NULL and we are not adding an element which is already adde
 *   if(node->left!=NULL && node!= stack_top(S)) {
 *	push(node->left);
 *	node = node->left;
 *
 *   } else {
 *	printf("%d", nod->val);
 *	pop();
 *	
 *	if(node->right!=NULL){
 *		node = node->right;
 *		push(node);
 *	} else {
 *	node = stack_top(); // get the pointer to top of stack. returns NULL if empty
 *	}
 *
 *   } //if-else ends
 *
 * }//while ends
 *  
 *}
 *
 */

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
//this function returns the new adjacency list for minimum spanning tree  for undirected graphs( note that
//this MST list allocates new memory, which is different than original graph


/*
 *minimum spanning tree: 
 *
 *A tree is a connected graph with no cycles.A spanning tree is a subgraph of G which has the same set of vertices of G and is a tree. 
 *A mininum spanning tree of a weighted graph G is the spanning tree of G whose edges sum to minimum weight. There can be more than one spanning tree in a graph -> consider a graph with identical weight edges
 *
 *
 *https://www.youtube.com/watch?v=LOak_hxG49g&index=10&list=PLPk0UGJMykbEONivKJXMXGiiKrJ3Ef_34
 */


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

/*check if the graph is bipartite or not*/
int main() {
    char c;
    int choice, n, i, j,  adj, elen, vtx;
    GRAPH *g = NULL;
    GRAPH* gclone = NULL;

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
	printf("10 -- single source shortest path using BFS(when all edge len = 1)\n");
	printf("11 -- clone the graph\n");

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
	        prims_MST();
		break;

	    case 4:
		printf("Enter the source vertex in graph\n");
		scanf("%d", &vtx);
		clear_visited_vertex(g, n);
		BFS(g, vtx, n);


		break;

	    case 5:
		break;

	    case 6:
		break;

	    case 7:
		topological_sort(g, n);
		print_topological_order(g, n);
		break;

	    case 10:
		printf("Enter the source vertex to get shortest distance from\n");
		scanf("%d", &vtx);
		clear_visited_vertex(g, n);
		BFS(g, vtx, n);
		printf("\n");
		print_shortest_dist(g, n);
		break;

	    case 11:
		if(!g)
		    printf("create the graph first using option 1\n");
		gclone = (GRAPH*)malloc(sizeof(GRAPH)*n);
		init_graph(gclone, n);
		DFS_clone(g, 0, gclone);
		print_graph(gclone, n);
		break;


	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}

