#include <iostream>
#include <utility> // for pair
#include <list>    // for list
#include <climits> // for INT_MAX
using namespace std;

struct Edge
{
    int src, dest, weight;
};

class Graph
{
    int V, E;
    Edge *list;
    int i = 0;

public:
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
        list = new Edge[E];
    }

    void addEdge(int u, int v, int w)
    {
        list[i].src = u;
        list[i].dest = v;
        list[i].weight = w;
        i++;
    }

    bool bellmanford(int source)
    {
        int dist[V];
        dist[source] = 0;

        for (int i = 0; i < V - 1; i++)
        {
            for (int j = 0; j < E; j++)
            {
                if (dist[list[j].dest] > dist[list[j].src] + list[j].weight)
                {
                    dist[list[j].dest] = dist[list[j].src] + list[j].weight;
                }
            }
        }

        for (int j = 0; j < E; j++) // Check if -ve cycle exists
        {
            if (dist[list[j].dest] > dist[list[j].src] + list[j].weight)
            {
                return false;
            }
        }

        for (int i = 0; i < V; i++)
        {
            cout << "\n"
                 << i << " is " << dist[i];
        }
        return true;
    }
};

int main()
{
    int V = 5, E = 8; // Number of vertices in the graph
    Graph g(V, E);

    // adding edges in the graph
    g.addEdge(0, 1, -1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 2, 5);
    g.addEdge(3, 1, 1);
    g.addEdge(4, 3, -3);

    int source = 0;
    cout << "Distances from " << source << " to-";
    g.bellmanford(source);

    return 0;
}