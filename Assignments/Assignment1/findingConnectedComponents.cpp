#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

class Graph
{
    int n;
    list<int> *adj;

    void bfs(int v, int cnt, vector<bool> &visited, vector<int> &component_id);

public:
    Graph(int n);
    void addEdge(int v, int w);
    vector<int> connected_components();
};
Graph::Graph(int n)
{
    this->n = n;
    adj = new list<int>[n];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::bfs(int v, int cnt, vector<bool> &visited, vector<int> &component_id)
{

    visited[v] = true;
    component_id[v] = cnt;

    queue<int> q;
    q.push(v);

    while (!q.empty())
    {
        v = q.front();
        q.pop();
        for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
        {

            if (visited[*it])
            {

                continue;
            }
            q.push(*it);
            visited[*it] = true;
            component_id[*it] = cnt;
        }
    }
}
vector<int> Graph::connected_components()
{
    vector<bool> visited(n, false);
    vector<int> component_id(n);
    int cnt = 0;
    for (int i = 0; i < n; i++)

    {
        if (!visited[i])
        {
            cnt++;
            bfs(i, cnt, visited, component_id);
        }
    }
    return component_id;
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

    vector<int> ids = g.connected_components();
    for (int i = 0; i < n; i++)
    {
        cout << ids[i] << "\n";
    }
    return 0;
}