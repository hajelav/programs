#include "graph.h"

void init_edge(EDGE *g) {

    g->shortest_edge = INT_MAX;
    g->from_vtx = INT_MIN;
    g->to_vtx = INT_MIN;
}

void init_graph(GRAPH *g, int n){

    int i;
    if(!g || n<=0)
	return;

    for(i=0;i<n;i++){
	g[i].idx = i;
	g[i].torder = 0;
	g[i].gnode = NULL;
	g[i].dist = 0;
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

int is_all_nodes_processed(GRAPH *g, int n){

    int i;

    for(i=0;i<n;i++){
	if(!g[i].processed)
	    return 1;
    }
    return 0; 
}

int isVisited(GRAPH *g, int idx) {
    return(g[idx].processed);
}
