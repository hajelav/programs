#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>
 

//graph node
typedef struct gnode {
    int idx;
    struct gnode *next;
} GNODE;

//graph vertex
typedef struct graph {
    int idx; //index of vertex node(starting from index 0)
    GNODE *gnode;
    char val;
    char nextVal;
    unsigned int processed:1; //visited
} GRAPH;


typedef struct itr {

    GRAPH *g;
    int i;
    int nodes;

} ITR;

void init_graph(GRAPH *g, int n){

    int i;
    if(!g || n<=0)
	return;

    for(i=0;i<n;i++){
	g[i].idx = i;
	g[i].val = '\0';
	g[i].nextVal = '\0';
	g[i].gnode = NULL;
    }
}

void clear_visited_vertex(GRAPH *g, int n) {
    
    int i;
    if(!g || !n)
	return;

    for(i=0;i<n;i++){
	g[i].processed = 0;
    }

}

//create graph node
GNODE* create_gnode(int idx) {

    GNODE* gn = (GNODE*)malloc(sizeof(GNODE));
    if(!gn)
	return NULL;
    gn->idx = idx;
    gn->next = NULL;
    return gn;
}

void create_graph( GRAPH *g, int idx) {

    GNODE *gn, *temp;

    gn = create_gnode(idx);
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
	    printf("%c[nextVal=%c]-->", g[i].val, g[i].nextVal);
	while(trav){
	    printf("%c ", g[trav->idx].val);
	    trav = trav->next;
	}
	printf("\n");
    }
}

int isVisited(GRAPH *g, int idx) {
    return(g[idx].processed);
}


/* DFS : O(n+m), n - vertices, m - edges */
void DFS(GRAPH *g, int vtx, char *A, int *count) {

    GNODE *trav;

    if(isVisited(g, vtx)){
        /*if we reach here that means , we have already came to a vertex which is already visited.*/
        return;
    }

    g[vtx].processed = 1;
    trav = g[vtx].gnode;

    //printf("%c->", g[vtx].val);
    if(g[vtx].val != '*'){
        A[*count] = g[vtx].val;
        (*count)++;
    }

    while(trav){
        DFS(g, trav->idx, A, count);
        trav = trav->next;
    }
    //printf("%d->", g[vtx].val);
}

bool hasNext(ITR *itr) {

    GRAPH *g;
    if(!itr)
        return false;

    g = itr->g;
    if(!g)
        return false;

    if(itr->i == itr->nodes)
        return false;

    return g[itr->i].val?true:false;
}

char next(ITR *itr){

    int j;
    GRAPH *g;
    char nextVal, c;
    
    g = itr->g;
    nextVal = g[itr->i].nextVal;
    c = g[itr->i].val;

    for(j=itr->i+1; j < itr->nodes; j++){
            
        if(g[j].val == nextVal){
            break;
        }
    }

    itr->i = j;  // move the internal pointer to next valid node

    return c;
}


ITR* init_iterator(GRAPH *g, int n) {

    char *A;
    int count = 0;
    int i, j;

    ITR *itr;

    //allocate and initialize ITR
    itr = (ITR*)malloc(sizeof(ITR));

    //dfs first pass: store the DFS order into an array : note that in DFS we always go down and then right when we see '*'
    A = (char*)calloc(n, sizeof(char));
    DFS(g, 0, A, &count);

    /*for(i=0;i<n;i++){
        printf("%c ", A[i]);
    }*/

    /*after first pass we have the correct order of elemets stored in array A, Now to achieve O(1) time for has next, we store 
     * the next value into each vertex of the graph
     */
    i=0; //starting index of graph  data sructure
    j = 1;  // starting index of array A
    while(i < n-1) {

        if(g[i].val == '*') {
            i++;
        }
        else{
            g[i].nextVal = A[j];
            i++;
            j++;

        }
    }


    //assign the iterator
    itr->g = g;
    for(i=0;i<n;i++){
        if(itr->g[i].val != '*'){
            break;
        }
    }
    itr->i = i;
    itr->nodes = n; //total number of nodes in the graph


    return itr;

}

int main() {

    int vtx, i, adj, j;
    int n; //no of nodes in the graph
    GRAPH *g = NULL;
    char value;
    ITR *itr;


    printf("Enter the number of vertices in graph\n");
    scanf("%d", &n);

    g = (GRAPH*)malloc(sizeof(GRAPH)*n);
    init_graph(g, n);
    for(i=0;i<n;i++){
        printf("enter value for vertex %d\n", i);
        scanf(" %c", &value);
        g[i].val = value;
        printf("Enter no of adjacent nodes to vertex %d\n", i);
        scanf("%d", &adj);
        //printf("%d", adj);
        for(j=0;j<adj;j++){
            printf("enter vertex\n");
            scanf("%d", &vtx);
            create_graph(&g[i], vtx);
        }
    }


    

    itr = init_iterator(g, n);
    print_graph(g, n); // graph DS is modified after initializing the iterator

    while(hasNext(itr)){
        printf("%c ", next(itr));
    }

    printf("\n");

return 0;
}
