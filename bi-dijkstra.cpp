#include <iostream>
#include <utility> // for pair
#include <list>    // for list
// #include <climits> // for INT_MAX
#define INT_MAX 1e9
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

    int dijkstra(int source, int goal)
    {
        pair<int, bool> df[V];
        pair<int, bool> db[V];
        int start = source, end = goal, minf, minb;
        for (int i = 0; i < V; i++)
        {
            df[i].first = INT_MAX;
            df[i].second = false;
            db[i].first = INT_MAX;
            db[i].second = false;
        }

        df[source].first = 0;
        db[goal].first = 0;

        for (int j = 0; j < V; j++)
        {
            //iterate over start edge and check df
            for (auto it = edges[start].begin(); it != edges[start].end(); ++it)
            {
                if (df[(*it).first].first > (df[start].first + (*it).second))
                {
                    df[(*it).first].first = df[start].first + (*it).second; // calculating dinstances from the element in priority queue
                }
                df[start].second = true; // marking the element as traversed in priority queue
            }

            //iterate over end edge and check db
            for (auto it = edges[end].begin(); it != edges[end].end(); ++it)
            {
                if (db[(*it).first].first > (db[end].first + (*it).second))
                {
                    db[(*it).first].first = db[end].first + (*it).second; // calculating distances from the element in priority queue
                }
                db[end].second = true; // marking the element as traversed in priority queue
            }

            minf = INT_MAX, minb = INT_MAX, start = V, end = -1;

            for (int i = 0; i < V; i++) // calculating next in priority queues of f and b
            {
                if (df[i].second)
                {
                    if (db[i].second)
                    {
                        int min = INT_MAX;
                        for (int j = 0; j < V; j++)
                        {
                            if (min > df[j].first + db[j].first)
                                min = df[j].first + db[j].first;
                        }
                        return min;
                    }
                }
                else
                {
                    if (df[i].first < minf)
                    {
                        start = i;
                        minf = df[i].first;
                    }

                    if (!db[i].second && db[i].first < minb)
                    {
                        end = i;
                        minb = db[i].first;
                    }
                }
            }
        }
        return -1;
    }
};

int main()
{
    int V, E, source, u, v, w;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;
    Graph g(V);

    for (int i = 0; i < E; i++) // adding edges in the graph
    {
        cout << "For edge " << i << ", enter source, destination and weight: ";
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    cout << "Enter the source from which you want to calculate distance: ";
    cin >> source;
    cout << "Distances from " << source << " to-";
    for (int goal = 0; goal < V; goal++)
    {
        cout << "\n"
             << goal << " is " << g.dijkstra(source, goal);
    }

    // example graph 1(9)
    // g.addEdge(0, 1, 4);
    // g.addEdge(0, 7, 8);
    // g.addEdge(1, 2, 8);
    // g.addEdge(1, 7, 11);
    // g.addEdge(2, 3, 7);
    // g.addEdge(2, 8, 2);
    // g.addEdge(2, 5, 4);
    // g.addEdge(3, 4, 9);
    // g.addEdge(3, 5, 14);
    // g.addEdge(4, 5, 10);
    // g.addEdge(5, 6, 2);
    // g.addEdge(6, 7, 1);
    // g.addEdge(6, 8, 6);
    // g.addEdge(7, 8, 7);

    return 0;
}