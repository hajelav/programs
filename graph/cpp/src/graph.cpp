#include "graph.h"

using namespace std;

void Graph::clearVisited(void) {

    /*initialize the visited array to 0*/
    for(int i=0; i<m_vertices; i++){
        m_visited[i] = 0;
    }
}

Graph::Graph(int vertices) {
    
    m_vertices = vertices;
    m_g.resize(vertices); //create an adjacency list equal to number of vertices
    m_visited.resize(vertices);  // array to remember visited nodes // array to remember visited nodes

    clearVisited();
}

void Graph::addEdge(int startNode, int endNode) {
    //add and edge to the graph
    m_g[startNode].push_back(endNode);
    //m_g[endNode].push_back(startNode);  //uncomment for bi-directional graph
}

void Graph::printGraph() {

    int v;

    for (v=0; v < m_vertices; v++) {
        cout << v << "-->";
        for (auto l : m_g[v]) {
            cout << l << " ";
        }
        cout << endl;
    }
}

/*queue implementation of BFS : run BFS from a given node*/
void Graph::BFS(int node) {
   
    list<int> q; //using list as a queue
    int vertex;
   /*bfs using the node passed as argument*/

   /*initialize the list with the first node*/
    q.push_back(node);
    /*mark the first node as visited*/
    m_visited[q.front()] = 1;
    
    while(!q.empty()) {

        vertex = q.front();
        /*iterate through the adjacency list*/
        for(auto n : m_g[vertex]) {
            /*if the node is not already visited, add it to the queue*/
            if(!m_visited[n]) {
                /*mark the node as visited*/
                m_visited[n] = 1;
                q.push_back(n);
            }

        }
        /*print and pop from the front of the queue */
        cout << vertex << " " ;
        q.pop_front();
    }
}

/*stack implementation of DFS : running DFS from a given node*/
void Graph::DFS_stack(int node) {

    list<int> s; //using list as a stack
    int vertex;
    bool flag = false;
    
    clearVisited(); //clear the visited array

    /*push the node into the stack*/
    s.push_back(node);
    /*mark the first node in the stack as visited*/
    m_visited[s.back()] = 1;

    while(!s.empty()) {

        flag = false;
        vertex = s.back();
        for ( auto n : m_g[vertex] ) {
            if(!m_visited[n]) {
                m_visited[n] = 1;
                s.push_back(n);
                flag = true;
                break;
            }
        }
        
        /*the flag is used to pop the stack only when all the adjacent nodes of a 
        vertex are already been visited. If the flag is true , then it means that not all 
        edges , adjacent to vertex were visited*/
        if(!flag) {
            cout << vertex << " ";
            s.pop_back();
        }
    }
}


bool Graph::DFS_cycle(int node) {

    list<int> s; //using list as a stack
    int vertex;
    bool flag = false;
    
    clearVisited(); //clear the visited array

    /*push the node into the stack*/
    s.push_back(node);
    /*mark the first node in the stack as visited*/
    m_visited[s.back()] = 1;

    while(!s.empty()) {

        flag = false;
        vertex = s.back();
        for ( auto n : m_g[vertex] ) {
            if(!m_visited[n]) {
                m_visited[n] = 1;
                s.push_back(n);
                flag = true;
                break;
            } else {
                /*if we have reached here, it means that we have found an edge, to a
                previously visited node ( a cycle )*/
                cout << "hello" << endl;
                return true;

            }
        }
        
        /*the flag is used to pop the stack only when all the adjacent nodes of a 
        vertex are already been visited. If the flag is true , then it means that not all 
        edges , adjacent to vertex were visited*/
        if(!flag) {
            //cout << vertex << " ";
            s.pop_back();
        }
    }

    return false;
}

