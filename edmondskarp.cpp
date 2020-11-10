// Program Author: Mashu Ajmera

#include <iostream> // for i/o
#include <climits>  // for INT_MAX
#include <queue>    // for queues
using namespace std;
const int V = 6; // Number of vertices in the graph

bool bfs(int rgraph[][V], int s, int t, int parent[]) // Breadth First Search (BFS) to find the shortest path from s to t
{
    bool visited[V] = {false}; // we save whether the junction has been visited
    queue<int> q;
    visited[s] = true; // we start by visiting the source
    q.push(s);         // we start by pushing q in the queue
    parent[s] = -1;    // we make the parent of the source as -1
    while (!q.empty()) // untill there is no junction left to be explored in the queue
    {
        int n = q.front();
        for (int i = 0; i < V; i++)
            if (!visited[i] && rgraph[n][i] > 0) // if the junction has not been visited and there is some residual capacity in the pipe
            {
                q.push(i);         // we add the junction in the queue
                visited[i] = true; // mark the junction as visited
                parent[i] = n;
            }

        q.pop(); // we pop the explored junction out
    }
    return visited[t]; // we return wheter we were label to reach terminal as we start from s
}

int edmondsKarp(int graph[][V], int s, int t)
{
    int maxFlow = 0, parent[V], rgraph[V][V], min; // we save the shortest path in the parent array, we save the residual capacity in the rgraph array

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            rgraph[i][j] = graph[i][j]; // we initialize the residual capacity as the original capacity of the pipes

    while (bfs(rgraph, s, t, parent)) // we check if a path exists from s to t, if so then we know it is saved in the parents aarray
    {
        min = INT_MAX;
        for (int i = t; i != -1; i = parent[i]) // we calculate the pipe with the minimum capacity in our shortest path
            if (min > rgraph[parent[i]][i])
                min = rgraph[parent[i]][i];

        for (int i = t; i != -1; i = parent[i]) // we now since all the pipes in the shortest path will be filled with min, we decrease their residual capacities by min
        {
            rgraph[parent[i]][i] -= min;
            rgraph[i][parent[i]] += min;
        }
        maxFlow += min; // we add all the flows to calculate our maximum flow
    }
    return maxFlow; //  we return the maximum flow calculated
}

int main() // the driver function for our implementation of Edmonds Karp Algorithm
{
    int graph[V][V], s, t;

    cout << "Enter the graph matrix of " << V << " vertices:\n";
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >>
                graph[i][j];

    cout << "Enter the source node: ";
    cin >> s;
    cout << "Enter the terminal node: ";
    cin >> t;

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
    // int graph[V][V] = {{0, 16, 13, 0, 0, 0},
    //                    {0, 0, 10, 12, 0, 0},
    //                    {0, 4, 0, 0, 14, 0},
    //                    {0, 0, 9, 0, 0, 20},
    //                    {0, 0, 0, 7, 0, 4},
    //                    {0, 0, 0, 0, 0, 0}};

    cout << "Maximum flow possible is: " << edmondsKarp(graph, s, t);
    return 0;
}