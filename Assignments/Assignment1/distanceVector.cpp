#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

class Graph
{
    int n;
    list<int> *adj;

public:
    vector<int> bfs(int v);

    Graph(int n);
    void addEdge(int v, int w);
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

vector<int> Graph::bfs(int v)
{
    vector<bool> visited(n, false);
    vector<int> distance(n, -1);
    visited[v] = true;
    queue<int> q;
    q.push(v);

    distance[v] = 0;
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
            visited[*it] = true;
            q.push(*it);
            distance[*it] = distance[v] + 1;
        }
    }
    return distance;
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

    return 0;
}