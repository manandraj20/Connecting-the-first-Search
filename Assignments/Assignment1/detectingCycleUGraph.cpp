#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
int cycle_start = -1;
int cycle_end = -1;

class Graph
{
    int n;
    list<int> *adj;
    bool dfs(int v, bool visited[], vector<int> &parent, int par);
    bool bfs(int v, bool visited[], vector<int> &parent, vector<int> &distance);

public:
    Graph(int n);
    void addEdge(int v, int w);
    bool isCyclic();
};
Graph::Graph(int n)
{
    this->n = n;
    adj = new list<int>[n + 1];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}
bool Graph::dfs(int v, bool visited[], vector<int> &parent, int par)
{
    visited[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
    {
        if ((*it) == par)
            continue;
        if (visited[*it])
        {
            cycle_end = v;
            cycle_start = *it;
            return true;
        }
        parent[*it] = v;
        if (dfs(*it, visited, parent, parent[*it]))
            return true;
    }
    return false;
}
bool Graph::bfs(int v, bool visited[], vector<int> &parent, vector<int> &distance)
{
    visited[v] = true;
    queue<int> q;
    q.push(v);
    parent[v] = -1;
    distance[v] = 0;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
        {
            if ((*it) == parent[v])
                continue;
            if (visited[*it])
            {
                cycle_start = *it;
                cycle_end = v;
                return true;
            }
            visited[*it] = true;
            q.push(*it);
            distance[*it] += distance[v] + 1;
            parent[*it] = v;
        }
    }
    return false;
}

bool Graph::isCyclic()
{
    bool *visited = new bool[n + 1]; // considering vertices numbered 1 through n
    vector<int> parent;
    vector<int> distance;
    parent.assign(n + 1, -1);
    distance.assign(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        visited[i] = false;
    }
    // Using BFS
    for (int v = 1; v <= n; v++)
    {
        if (!visited[v] && bfs(v, visited, parent, distance))
            break;
    }
    // Using DFS
    // for (int v = 1; v <= n; v++)
    // {
    //     if (!visited[v] && dfs(v, visited, parent, parent[v]))
    //         break;
    // }
    if (cycle_start == -1)
    {
        return false;
    }
    // return true;
    vector<int> cycle;
    vector<int> cycle_2;
    cycle.push_back(cycle_start);
    // cout<<cycle_end<<" "<<" "<<parent[cycle_end]<<" " <<cycle_start<<"\n";
    // cout<<parent[parent[cycle_end]]<<"\n";
    for (int v = cycle_end; v != cycle_start; v = parent[v])
    {
        //  cout<<distance[cycle_end]-distance[cycle_start]<<"\n";
        if ((distance[cycle_start] == distance[cycle_end]) || (distance[cycle_end] - distance[cycle_start] == -1))
        {
            int w = cycle_start;
            if (distance[cycle_end] - distance[cycle_start] == -1)
            {
                //  cycle.push_back(v);
                w = parent[w];

                while (w != v)
                {
                    cycle.push_back(w);
                    cycle_2.push_back(v);
                    v = parent[v];
                    w = parent[w];
                }
                cycle.push_back(w);
            }
            else
            {
                //  cycle.push_back(v);
                while (w != v)
                {
                    //   cycle_2.push_back(w);
                    cycle.push_back(v);
                    v = parent[v];
                    w = parent[w];
                    cycle_2.push_back(w);
                }
                //  cycle.push_back(w);
            }
            break;
        }

        cycle.push_back(v);
    }
    if (cycle_2.size() > 0)
    {
        reverse(cycle_2.begin(), cycle_2.end());
        cycle.insert(cycle.end(), cycle_2.begin(), cycle_2.end());
    }

    cycle.push_back(cycle_start);

    // reverse(cycle.begin(), cycle.end());
    cout << cycle.size() << "\n";
    for (int v : cycle)
        cout << v << " ";
    return true;
}

int main()
{
    // your code goes here
    int n, m;

    cin >> n >> m;
    Graph g(n);
    int a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        g.addEdge(a, b);
        g.addEdge(b, a);
    }
    if (!g.isCyclic())
        cout << "IMPOSSIBLE";

    return 0;
}