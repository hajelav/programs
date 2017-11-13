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
    int costLib;
    GNODE *gnode;
    int torder; // topological order of the vertex
    unsigned int visited:1; //visited
    int dist;
} GRAPH;


/********************************* FUNCTIONS DEFINITIONS HERE ************************************/

void init_graph(GRAPH *g, int noOfVertex, int costLib){

    int i;
    if(!g || noOfVertex <= 0)
        return;

    for(i=1;i<=noOfVertex;i++){
        g[i].idx = i;
        g[i].torder = 0;
        g[i].gnode = NULL;
        g[i].costLib = costLib;
        g[i].dist = 0;
        g[i].visited = 0;
    }
}

void clear_visited_vertex(GRAPH *g, int n) {

    int i;
    if(!g || !n)
        return;

    for(i=0;i<n;i++){
        g[i].visited = 0;
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

int is_all_nodes_visited(GRAPH *g, int n){

    int i;

    for(i=0;i<n;i++){
        if(!g[i].visited)
            return 1;
    }
    return 0; 
}

int isVisited(GRAPH *g, int idx) {
    return(g[idx].visited);
}


int minCost(GRAPH *g, int noOfVertex, int costLib, int costRoad){

    if(costRoad > costRoad){
        return (noOfVertex*costLib);
    }

return 0;
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
    printf("enter number of queries\n");
    scanf("%i", &q);
    for(a0 = 0; a0 < q; a0++){
        printf("enter no of cities(vertex), no of roads(edge), cost of lib, cost of road\n");
        scanf("%i %i %li %li", &noOfCities, &noOfRoads, &costLib, &costRoad);
        g = (GRAPH*)malloc(sizeof(GRAPH)*(noOfCities+1));
        init_graph(g, noOfCities, costLib);

        for(a1 = 0; a1 < noOfRoads; a1++){
            printf("enter city1 , city2\n");
            scanf("%i %i", &city_1, &city_2);
            connect_vertex(g, city_1, city_2, costRoad); // connect edge from city1 to city2
            connect_vertex(g, city_2, city_1, costRoad); // connect edge from city2 to city1
        }
    }
    minCost(g, noOfCities, costLib, costRoad);
    print_graph(g, noOfCities);
    return 0;
}

