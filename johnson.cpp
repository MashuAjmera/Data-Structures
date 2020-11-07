#include <iostream>
#include <utility> // for pair
#include <list>    // for list
#include <climits> // for INT_MAX
using namespace std;

struct Edge
{
    int src, dest, weight;
};

class BellmanFord
{
    int V, E;
    Edge *list;
    int i = 0;

public:
    BellmanFord(int V, int E)
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

    int *calc(int source)
    {
        int *dist;
        dist = new int[V];
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

        return dist;
    }
};

class Dijkstra
{
    int V;
    list<pair<int, int>> *edges;

public:
    Dijkstra(int V)
    {
        this->V = V;
        edges = new list<pair<int, int>>[V];
    }

    void addEdge(int u, int v, int w)
    {
        edges[u].push_back(make_pair(v, w));
    }

    int *calc(int source)
    {
        // pair<int, bool> dist[V];
        int *dist;
        dist = new int[V];
        int queue[V];
        int start = source, min;
        for (int i = 0; i < V; i++)
        {
            dist[i] = INT_MAX;
            queue[i] = false;
        }

        dist[start] = 0;

        for (int j = 0; j < V; j++)
        {
            //iterate over start edge and check dist
            for (auto it = edges[start].begin(); it != edges[start].end(); ++it)
            {
                if (dist[(*it).first] > (dist[start] + (*it).second))
                {
                    dist[(*it).first] = dist[start] + (*it).second; // calculating distances from the element in priority queue
                }
                queue[start] = true; // marking the element as traversed in priority queue
            }

            min = INT_MAX, start = V;

            for (int i = 0; i < V; i++) // calculating next in priority queue
            {
                if (dist[i] < min && queue[i] == false)
                {
                    start = i;
                    min = dist[i];
                }
            }
        }

        return dist;
    }
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
    void johnson()
    {
        int *dist[V];
        BellmanFord bf(V + 1, V + E);

        for (int i = 0; i < E; i++)
        {
            bf.addEdge(list[i].src, list[i].dest, list[i].weight);
        }
        for (int i = 0; i < V; i++) // adding edges of s
        {
            bf.addEdge(V, i, 0);
        }

        int *h = bf.calc(V);

        Dijkstra da(V); // starting the dijkstra part
        for (int i = 0; i < E; i++)
        {
            da.addEdge(list[i].src, list[i].dest, list[i].weight + h[list[i].src] - h[list[i].dest]); // calculating the modified weight
        }
        for (int i = 0; i < V; i++)
        {
            dist[i] = da.calc(i);
            cout << "\n"
                 << i << ":";
            for (int j = 0; j < V; j++)
            {
                dist[i][j] = dist[i][j] - h[i] + h[j];
                cout << " " << dist[i][j];
            }
        }
    }
};

int main()
{
    int V, E, u, v, w;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;
    Graph g(V, E);

    for (int i = 0; i < E; i++) // adding edges in the graph
    {
        cout << "For edge " << i << ", enter source, destination and weight: ";
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    cout << "The disance matrix is:";
    g.johnson();

    // example graph 1(4,7)
    // g.addEdge(0, 1, -3);
    // g.addEdge(0, 3, 2);
    // g.addEdge(1, 0, 5);
    // g.addEdge(1, 2, 3);
    // g.addEdge(2, 0, 1);
    // g.addEdge(3, 0, -1);
    // g.addEdge(3, 2, 4);

    //example graph 2(4,5)
    // g.addEdge(0, 1, -5);
    // g.addEdge(0, 2, 2);
    // g.addEdge(0, 3, 3);
    // g.addEdge(1, 2, 4);
    // g.addEdge(2, 3, 1);

    return 0;
}