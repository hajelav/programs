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

    Graph g(4); 
    g.addEdge(0, 1); 
    g.addEdge(0, 2); 
    g.addEdge(1, 2); 
    //g.addEdge(2, 0); 
    g.addEdge(2, 3); 
    //g.addEdge(3, 3); 
    //g.addEdge(1, 0); 

    g.printGraph();
    //g.BFS(0);
    //g.DFS_stack(2);
    cout << endl;
    cout << "DFS cycle = " << g.DFS_cycle(0) << endl;

    return 0;
}
