#include <iostream>
#include <utility> // for pair
#include <list>    // for list
#include <climits> // for INT_MAX
#include <queue>
using namespace std;

struct Edge
{
    int dest, cpty, flow;
    Edge(int dest, int cpty)
    {
        this->dest = dest;
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
    list<Edge *> *edges;
    list<pair<int, list<int>>> L;

    void preflow(int s)
    {
        for (int i = 0; i < V; i++)
        {
            vertices[i].h = 0;
            vertices[i].e = 0;
        }
        vertices[s].h = V;
        for (auto it = edges[s].begin(); it != edges[s].end(); ++it)
        {
            (*it)->flow = (*it)->cpty;
            vertices[(*it)->dest].e = (*it)->flow;
        }
    }

    void relabel(int u)
    {
        if (vertices[u].e > 0)
        {
            int min = INT_MAX;
            for (auto it = edges[u].begin(); it != edges[u].end(); ++it)
            {
                if ((*it)->cpty > (*it)->flow && vertices[u].h <= vertices[(*it)->dest].h)
                {
                    if (min > vertices[(*it)->dest].h)
                    {
                        min = vertices[(*it)->dest].h;
                    }
                }
            }
            vertices[u].h = 1 + min;
        }
    }

    void push(int u, int v)
    {
        if (vertices[u].e > 0)
        {
            for (auto it = edges[u].begin(); it != edges[u].end(); ++it)
            {
                if ((*it)->dest == v && (*it)->cpty > (*it)->flow && vertices[u].h > vertices[v].h)
                {
                    int df = min(vertices[u].e, (*it)->cpty - (*it)->flow);
                    (*it)->flow += df;
                    vertices[u].e -= df;
                    vertices[v].e += df;
                }
            }
        }
    }

    void discharge(list<pair<int, list<int>>>::iterator u)
    {
        auto v = (*u).second.begin();
        while (vertices[(*u).first].e > 0)
        {
            if (v == (*u).second.end())
            {
                relabel((*u).first);
                v = (*u).second.begin();
            }
            else if (vertices[(*u).first].h == vertices[*v].h + 1) //see
            {
                push((*u).first, *v);
                break;
            }
            else
                ++v;
        }
    }

public:
    Graph(int V)
    {
        this->V = V;
        edges = new list<Edge *>[V];
        vertices = new Vertex[V];
    }

    void addEdge(int src, int dest, int cpty)
    {
        edges[src].push_back(new Edge(dest, cpty));
    }

    int relabelToFront(int s, int t)
    {
        preflow(s);
        for (int i = 1; i < V - 1; i++)
        {
            list<int> neighbour;
            for (auto u = edges[i].begin(); u != edges[i].end(); ++u)
            {
                neighbour.push_back((*u)->dest); //see
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
            }
        }
        return vertices[t].e;
    }
};

int main()
{
    int V = 6; // Number of vertices in the graph
    Graph g(V);

    // Adding edges and their capacities
    g.addEdge(0, 1, 16);
    g.addEdge(0, 2, 13);
    g.addEdge(1, 2, 10);
    g.addEdge(2, 1, 4);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);

    int s = 0, t = 5;
    cout << "Maximum Flow possible is: " << g.relabelToFront(s, t);

    return 0;
}
