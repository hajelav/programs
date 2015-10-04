/**
 * @file    : graph_util.c
 * @brief   : graph util API
 * @author  : Vivek Hajela
 * @version : 0.1
 * @date    : 2015-10-03
 */

#include "graph_util.h"

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
    printf("NODES     NEIGHBORS\n");
    for(i=0;i<n;i++){
	trav = g[i].gnode;
	    printf("node[%lu]-->", i);
	while(trav){
	    printf("%lu ", trav->idx);
	    trav = trav->next;
	}
	printf("\n");
    }
    printf("\n");
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

void free_graph(GRAPH *g, uint64_t n) {

    uint64_t i;
    GNODE *trav;

    if(!g)
	return;

    for(i=0;i<n;i++){
	trav = g[i].gnode;
	while(trav){
	    g[i].gnode = trav->next;
	    /*printf("free node[%lu]\n", trav->idx);*/
	    free(trav);
	    trav = g[i].gnode;
	}
    }

    free(g);
}

/*read graph from the input text file*/
int read_graph(GRAPH *g, char *file_name, uint64_t n) {

    char line[512];
    char *token;
    FILE *fp;
    uint64_t i, node;


    if(!g || !file_name || (n<=0))
	return -1;

    /*open the file*/
    fp = fopen(file_name, "r");

    if(!fp){
	perror("error opening input file\n");
 	return -1;	
    }
    i = 0;
    while(fgets(line, sizeof line, fp) != NULL) {
        token = strtok(line, " ");
        i = atoi(token);
	token = strtok(NULL, " ,");
        while(token != NULL) {
            node  = atoi(token);
	    /*printf("%d-->%d ", i , node);*/
	    create_graph(&g[i], node);
            token = strtok(NULL, " ");
        }
	/*printf("\n");*/
    }
    return 1;
}
