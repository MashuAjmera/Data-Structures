#include <iostream>
#include <climits> // for INT_MAX
#include <queue>   // for queues
using namespace std;
const int V = 6; // Number of vertices in the graph

bool bfs(int rgraph[][V], int s, int t, int parent[])
{
    bool visited[V] = {false};
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty())
    {
        int n = q.front();
        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && rgraph[n][i] > 0)
            {
                q.push(i);
                visited[i] = true;
                parent[i] = n;
            }
        }
        q.pop();
    }
    return visited[t];
}

int edmondsKarp(int graph[][V], int s, int t)
{
    int maxFlow = 0, parent[V], rgraph[V][V], min;

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            rgraph[i][j] = graph[i][j];

    while (bfs(rgraph, s, t, parent))
    {
        min = INT_MAX;
        for (int i = t; i != -1; i = parent[i])
        {
            if (min > rgraph[parent[i]][i])
            {
                min = rgraph[parent[i]][i];
            }
        }
        for (int i = t; i != -1; i = parent[i])
        {
            rgraph[parent[i]][i] -= min;
            // rgraph[i][parent[i]] += min;
        }
        maxFlow += min;
    }
    return maxFlow;
}

int main()
{
    // Test Case-1: V=6, s=0,t=5, ans=10
    // int graph[V][V] = {{0, 7, 4, 0, 0, 0},
    //                    {0, 0, 0, 5, 3, 0},
    //                    {0, 3, 0, 0, 2, 0},
    //                    {0, 0, 0, 0, 0, 8},
    //                    {0, 0, 0, 3, 0, 5},
    //                    {0, 0, 0, 0, 0, 0}};

    // Test Case-2: V=4, s=0,t=3, ans=2000000
    // int graph[V][V] = {{0, 1000000, 1000000, 0},
    //                    {0, 0, 1, 1000000},
    //                    {0, 0, 0, 1000000},
    //                    {0, 0, 0, 0}};

    // Test Case-3: V=4, s=0,t=3, ans=20
    // int graph[V][V] = {{0, 10, 10, 0},
    //                    {0, 0, 5, 15},
    //                    {0, 7, 0, 8},
    //                    {0, 0, 0, 0}};

    // Test Case-4: V=6, s=0,t=5, ans=23
    int graph[V][V] = {{0, 16, 13, 0, 0, 0},
                       {0, 0, 10, 12, 0, 0},
                       {0, 4, 0, 0, 14, 0},
                       {0, 0, 9, 0, 0, 20},
                       {0, 0, 0, 7, 0, 4},
                       {0, 0, 0, 0, 0, 0}};

    int s = 0, t = 5;
    cout << "Maximum Flow possible is: " << edmondsKarp(graph, s, t);

    return 0;
}