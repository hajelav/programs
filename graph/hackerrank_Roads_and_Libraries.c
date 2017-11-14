#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>


/********************************** STRUCTURE DEFINITIONS ****************************************/
//graph node
typedef struct gnode {
    int idx;
    int edge_len;
    struct gnode *next;
} GNODE;

//graph vertex
typedef struct graph {
    int idx; //index of vertex node
    long int costLib;
    GNODE *gnode;
    int torder; // topological order of the vertex
    unsigned int visited:1; //visited
    int distFromSrcVertex;
} GRAPH;


/********************************* FUNCTIONS DEFINITIONS HERE ************************************/

void init_graph(GRAPH *g, int noOfVertex, long int costLib){

    int i;
    if(!g || noOfVertex <= 0)
        return;

    for(i=1;i<=noOfVertex;i++){
        g[i].idx = i;
        g[i].torder = 0;
        g[i].gnode = NULL;
        g[i].costLib = costLib;
        g[i].distFromSrcVertex = 0;
        g[i].visited = 0;
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

void connect_vertex( GRAPH *g, int fromVertex, int toVertex, int edgeLen) {

    GNODE *gn, *temp;

    gn = create_gnode(toVertex, edgeLen);
    if(!gn)
        return;
    if(!g[fromVertex].gnode){ 
        g[fromVertex].gnode = gn;
    } else {
        temp = g[fromVertex].gnode;
        g[fromVertex].gnode  = gn;
        gn->next = temp;
    }
}

void print_graph(GRAPH *g, int n) {
    int i;
    GNODE *trav;

    for(i=1;i<=n;i++){
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
 *BFS  for directed/undirected graphs
 *Note : BFS can also be used to compute the shortest path from  a single source to all destinations, when all 
 *edge lenghts of a graph are equal(say 1)
 */

//while we put the edges into the queue, we also count it. the solution would be to sum all the edges for
long int enqueue(GRAPH** q, GRAPH* g, int front, int *end) {

    long int noOfEdges = 0;

    GNODE *trav;

    if(q[front] == NULL)
	return 0;

    //get the neigbor vertices of q[front]
    trav = q[front]->gnode;

    while(trav){
	/*insert into the q only if the vertex is not visited*/
	if(!g[trav->idx].visited){

	    noOfEdges = noOfEdges + 1;
	    q[*end] = &g[trav->idx];
	    //update the distance
	    q[*end]->distFromSrcVertex = q[front]->distFromSrcVertex + 1;
	    (*end)++;
	    g[trav->idx].visited = 1;
	}
	trav = trav->next;
    }
    return noOfEdges;
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
long int BFS( GRAPH *g, int src, int n) {

    int front = 0, end; 
    GRAPH **q;
    long int noOfEdges = 0;

    //create a queue of n(no of vertices) pointers to the the graph nodes
    q  = (GRAPH**)malloc(sizeof(GRAPH*)*n);

    //initialize the queue with source vertex
    q[0] =  &g[src];

    //mark the src index as visited
    q[0]->visited = 1;
    //intitalize front to 0(queue is deleted from front)
    front = 0;
    //intitalize end to front+1(queue is inserted)
    end = front + 1;

    while(front!=end) {
        //insert the neighbors from the end of queue
        noOfEdges += enqueue(q, g, front, &end);

        //print from the front and dequeue 
        //printf("%d-->", q[front]->idx);

        //delete from the front
        dequeue(q, &front);
    }
    return noOfEdges;
}

long int minCost(GRAPH *g, int noOfVertex, long int costLib, long int costRoad){

    int i;
    long int minCost = 0;
    if(costRoad > costLib){
        return (noOfVertex*costLib);
    }

    /*run BFS through all disconnected components, and add up the the total cost*/
    for(i = 1; i <= noOfVertex; i++){
        if(!g[i].visited){
            g[i].visited = 1;
            minCost = minCost + costLib + (BFS(g, i, noOfVertex) * costRoad);
        }
    }

    return minCost;   
}


int main() {

    GRAPH *g;
    int a0, a1;
    int noOfCities; 
    int noOfRoads; 
    long int costLib; 
    long int costRoad; 
    int city_1; 
    int city_2; 

    int q; 
    //printf("enter number of queries\n");
    scanf("%i", &q);
    for(a0 = 0; a0 < q; a0++){
      //  printf("enter no of cities(vertex), no of roads(edge), cost of lib, cost of road\n");
        scanf("%i %i %li %li", &noOfCities, &noOfRoads, &costLib, &costRoad);
        g = (GRAPH*)malloc(sizeof(GRAPH)*(noOfCities+1));
        init_graph(g, noOfCities, costLib);

        for(a1 = 0; a1 < noOfRoads; a1++){
        //    printf("enter city1 , city2\n");
            scanf("%i %i", &city_1, &city_2);
            connect_vertex(g, city_1, city_2, costRoad); // connect edge from city1 to city2
            connect_vertex(g, city_2, city_1, costRoad); // connect edge from city2 to city1
        }
    printf(" %ld\n", minCost(g, noOfCities, costLib, costRoad));
    }
    //print_graph(g, noOfCities);
    return 0;
}

