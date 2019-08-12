#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

typedef vector<int> node;

class Graph {

    private:
        int m_vertices;         //no of vertices
        vector<node> m_g;       //adjacency list ( vector<vector<int>> m_g )
        vector<int> m_visited; 
        vector<int> m_topological_order;

    public:
        Graph(int vertices);
        void addEdge(int startNode, int endNode);
        void printGraph();
        void BFS(int node);
        void DFS_stack(int node);
        void DFS(int node);
        void clearVisited(void);
        bool DFS_cycle(int node);
        void DFS_topological_sort();
        void print_topological_order();
        void DFS_topological_sort_util(int node, int *curr_node);
};
