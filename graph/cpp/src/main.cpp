#include "graph.h"


int main() {

    /*
     *Graph g(5);
     *g.addEdge(0,1);
     *g.addEdge(0,4);
     *g.addEdge(1,2);
     *g.addEdge(1,3);
     *g.addEdge(1,4);
     *g.addEdge(2,3);
     *g.addEdge(3,4);
     */
/*
 *
 *    Graph g(4); 
 *    g.addEdge(0, 1); 
 *    g.addEdge(0, 2); 
 *    g.addEdge(1, 2); 
 *    g.addEdge(2, 0); 
 *    g.addEdge(2, 3); 
 *    g.addEdge(3, 3); 
 *    g.addEdge(1, 0); 
 */


    Graph g(6); 
    g.addEdge(5, 2); 
    g.addEdge(5, 0); 
    g.addEdge(4, 0); 
    g.addEdge(4, 1); 
    g.addEdge(2, 3); 
    g.addEdge(3, 1); 

    g.printGraph();
    //g.DFS_topological_sort();
    //g.print_topological_order();
    //g.BFS(0);
    g.DFS_stack(0);
    cout << endl;
    //cout << "DFS cycle = " << g.DFS_cycle(0) << endl;

    return 0;
}
