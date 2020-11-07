#include <iostream>
#include <utility> // for pair
#include <list>    // for list
#include <climits> // for INT_MAX
using namespace std;

class Graph
{
    int V;
    list<pair<int, int>> *edges;

public:
    Graph(int V)
    {
        this->V = V;
        edges = new list<pair<int, int>>[V];
    }

    void addEdge(int u, int v, int w)
    {
        edges[u].push_back(make_pair(v, w));
        edges[v].push_back(make_pair(u, w));
    }

    void dijkstra(int source)
    {
        pair<int, bool> dist[V];
        int start = source, min;
        for (int i = 0; i < V; i++)
        {
            dist[i].first = INT_MAX;
            dist[i].second = false;
        }

        dist[start].first = 0;

        for (int j = 0; j < V; j++)
        {
            //iterate over start edge and check dist
            for (auto it = edges[start].begin(); it != edges[start].end(); ++it)
            {
                if (dist[(*it).first].first > (dist[start].first + (*it).second))
                {
                    dist[(*it).first].first = dist[start].first + (*it).second; // calculating distances from the element in priority queue
                }
                dist[start].second = true; // marking the element as traversed in priority queue
            }

            min = INT_MAX, start = V;

            for (int i = 0; i < V; i++) // calculating next in priority queue
            {
                if (dist[i].first < min && dist[i].second == false)
                {
                    start = i;
                    min = dist[i].first;
                }
            }
        }

        for (int i = 0; i < V; i++)
        {
            cout << "\n"
                 << i << " is " << dist[i].first;
        }
    }
};

int main()
{
    int V = 9; // Number of vertices in the graph
    Graph g(V);

    // adding edges in the graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    int source = 0;
    cout << "Distances from " << source << " to-";
    g.dijkstra(source);

    return 0;
}