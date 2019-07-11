#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

typedef vector<int> node;

class Graph {

    private:
        int m_vertices;         //no of vertices
        vector<node> m_g;       //adjacency list
        vector<int> m_visited; 

    public:
        Graph(int vertices);
        void addEdge(int startNode, int endNode);
        void printGraph();
        void BFS(int node);
        void DFS_stack(int node);
        void clearVisited(void);
        bool DFS_cycle(int node);
};
