#include <iostream>
using namespace std;
#include <utility>
#include <climits>
// Number of vertices in the graph
const int V = 9;

void dijkstra(int graph[][V], int source)
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
        for (int i = 0; i < V; i++) // calculating distances from the element in priority queue
        {
            if (graph[start][i] != 0 && dist[i].first > (dist[start].first + graph[start][i]))
            {
                dist[i].first = dist[start].first + graph[start][i];
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
// -1 4 -1 -1 - 1-1 -1 8 -1

int main()
{
    /* Let us create the example graph discussed above */
    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                       {0, 0, 4, 14, 10, 0, 2, 0, 0},
                       {0, 0, 0, 0, 0, 2, 0, 1, 6},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}};
    int source = 0;
    cout << "Distances from " << source << " to-";
    dijkstra(graph, source);
    return 0;
}