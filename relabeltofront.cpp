#include <iostream>
#include <utility> // for pair
#include <list>    // for list
#include <climits> // for INT_MAX
#include <vector>  // for dynamic arrays
using namespace std;

struct Edge
{
    int cpty, flow;
    Edge(int cpty = 0)
    {
        this->cpty = cpty;
        this->flow = 0;
    }
};

struct Vertex
{
    int h, e;
};

class Graph
{
    int V;
    Vertex *vertices;
    vector<vector<Edge *>> edges;
    list<pair<int, list<int>>> L;

    void preflow(int s)
    {
        for (int i = 0; i < V; i++)
        {
            vertices[i].h = 0;
            vertices[i].e = 0;
        }
        vertices[s].h = V;
        for (int i = 0; i < V; i++)
        {
            edges[s][i]->flow = edges[s][i]->cpty;
            vertices[i].e = edges[s][i]->flow;
        }
    }

    void relabel(int u)
    {
        if (vertices[u].e > 0)
        {
            int min = INT_MAX;
            for (int v = 0; v < V; v++)
            {
                if (edges[u][v]->cpty > edges[u][v]->flow && vertices[u].h <= vertices[v].h && min > vertices[v].h)
                {
                    min = vertices[v].h;
                    vertices[u].h = 1 + min;
                }
            }
            cout << "flag1 min: " << min << "\n";
        }
    }

    void push(int u, int v)
    {
        if (vertices[u].e > 0)
        {
            if (edges[u][v]->cpty > edges[u][v]->flow && vertices[u].h > vertices[v].h)
            {
                int df = min(vertices[u].e, edges[u][v]->cpty - edges[u][v]->flow);
                edges[u][v]->flow += df;
                vertices[u].e -= df;
                vertices[v].e += df;
            }
        }
    }

    void discharge(list<pair<int, list<int>>>::iterator u)
    {
        auto v = (*u).second.begin();
        while (vertices[(*u).first].e > 0)
        {
            cout << "flag5 " << (*u).first << "\n";
            if (v == (*u).second.end())
            {
                relabel((*u).first);
                cout << "flag2 v: " << *v << " u: " << (*u).first << " excess(u) : " << vertices[(*u).first].e << "\n";
                v = (*u).second.begin();
            }
            else if (edges[(*u).first][*v]->cpty > edges[(*u).first][*v]->flow && vertices[(*u).first].h == vertices[*v].h + 1)
            {
                push((*u).first, *v);
                cout << "flag3 u: " << (*u).first << " excess(u) : " << vertices[(*u).first].e << "\n";
            }
            else
            {
                cout << "flag4 v: " << *v << "\n";
                ++v;
            }
        }
    }

public:
    Graph(int V)
    {
        this->V = V;
        vertices = new Vertex[V];
        edges.assign(V, vector<Edge *>(V, new Edge));
    }

    void addEdge(int src, int dest, int capacity)
    {
        edges[src][dest] = new Edge(capacity);
    }

    int relabelToFront(int s, int t)
    {
        preflow(s);
        for (int i = 1; i < V - 1; i++)
        {
            list<int> neighbour;
            for (int j = 0; j < V; j++)
            {
                if (edges[i][j]->cpty > 0 || edges[j][i]->cpty > 0)
                {
                    neighbour.push_back(j);
                }
            }
            L.push_back(make_pair(i, neighbour));
        }
        for (auto u = L.begin(); u != L.end(); ++u)
        {
            int old_height = vertices[(*u).first].h;
            discharge(u);
            if (vertices[(*u).first].h > old_height)
            {
                pair<int, list<int>> temp = *u;
                L.erase(u);
                L.push_front(temp);
                u = L.begin();
                cout << "flag7 u: " << (*u).first << "\n";
            }
        }
        return vertices[t].e;
    }
};

int main()
{
    int V, s, t, E;
    // Graph g(V);

    // Test Case: 1, ans=20
    V = 5, s = 0, t = 4;
    Graph g(V);
    g.addEdge(0, 1, 12);
    g.addEdge(0, 2, 14);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 4, 16);
    g.addEdge(2, 3, 8);
    g.addEdge(3, 1, 7);
    g.addEdge(3, 4, 10);

    // Test Case: 2, ans=23
    // V=6,s=0,t=5;
    // Graph g(V);
    // g.addEdge(0, 1, 16);
    // g.addEdge(0, 2, 13);
    // g.addEdge(1, 2, 10);
    // g.addEdge(2, 1, 4);
    // g.addEdge(1, 3, 12);
    // g.addEdge(2, 4, 14);
    // g.addEdge(3, 2, 9);
    // g.addEdge(3, 5, 20);
    // g.addEdge(4, 3, 7);
    // g.addEdge(4, 5, 4);

    cout << "Maximum Flow possible is: " << g.relabelToFront(s, t);

    return 0;
}
