#include <iostream>
#include <queue>
#include <list> // for list
using namespace std;

class Graph
{
    int V;
    list<int> *edges;

public:
    Graph(int V)
    {
        this->V = V;
        edges = new list<int>[V];
    }

    void addEdge(int src, int dest)
    {
        edges[src].push_back(dest);
    }

    bool bfs(int s, int t, int parent[])
    {
        bool visited[V] = {false};
        queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;
        while (!q.empty())
        {
            int n = q.front();
            for (auto it = edges[n].begin(); it != edges[n].end(); ++it)
            {
                if (!visited[*it])
                {
                    q.push(*it);
                    visited[*it] = true;
                    parent[*it] = n;
                }
            }
            q.pop();
        }
        return visited[t];
    }
};

int main()
{
    int V = 9; // Number of vertices in the graph
    Graph g(V);

    // adding edges in the graph
    g.addEdge(0, 1);
    g.addEdge(0, 7);
    g.addEdge(1, 2);
    g.addEdge(1, 7);
    g.addEdge(2, 3);
    g.addEdge(2, 8);
    g.addEdge(2, 5);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(6, 8);
    g.addEdge(7, 8);

    int s = 0, t = 8, parent[V];
    if (g.bfs(0, 5, parent))
    {
        cout << "The shortest path is: ";
        int i = t;
        for (int i = t; i != -1; i = parent[i])
        {
            cout << i << "<-";
        }
    }
    else
        cout << "No path exists from " << s << " to " << t << ".";

    return 0;
}