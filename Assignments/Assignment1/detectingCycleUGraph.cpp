#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int cycle_start = -1;// Track the start index of cycle if there is one.
int cycle_end = -1;

/*
Creating a class Grapn and having a public member function isCyclic() to check for cycle in a graph.
This solution considers that the vertices are numbered 1 through n, where n is the number of vertices.
*/
class Graph
{
    int n;
    list<int> *adj;
    bool dfs(int v, bool visited[], vector<int> &parent, int parent);
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
            continue; // The edge joining current vertex to its parent is skipped.
        if (visited[*it]) //If an already visited node (other than parent node) is encountered, there is a cycle.
        {
            cycle_end = v;
            cycle_start = *it;
            return true;
        }
        
        /*
         If there is no back edge. In DFS, (undirected graph) we can only tree edges and back edges, there is no chance for cross-edge.
         However, one can come across cross-edge in BFS. Forward edge is never possible in undirected graph.
         By cross-edge in BFS, we mean the edge which connects nodes in different branches.
        */
        
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
    /*
    When Using one of BFS or DFS, comment out the other not is use.
    Here DFS is in use. So, BFS has been commented out.
    */
    // Using BFS
//     for (int v = 1; v <= n; v++)
//     {
//         if (!visited[v] && bfs(v, visited, parent, distance))
//             break;
//     }
    // Using DFS
    for (int v = 1; v <= n; v++)
    {
        if (!visited[v] && dfs(v, visited, parent, parent[v])) // checking through all connected components
            break;
    }
    if (cycle_start == -1) // There was no cycle
    {
        return false;
    }
    vector<int> cycle;
    vector<int> cycle_2; // Used when there is a cross-edge in BFS.
    cycle.push_back(cycle_start);
    for (int v = cycle_end; v != cycle_start; v = parent[v]) // loop through all the elements of cycle
    {
        /*
        The following IF block is executed only if we do BFS and in BFS we encounter our cycle through cross-edge. 
        By cross-edge in BFS, we mean the edge which connects nodes(i.e.,vertices) in different branches.
        Also there is a theorem:
        Let T be a BFS tree, let x and y be nodes in T belonging tp layers i and j and let (x, y) be and edge of G.
        Then i and j differ by atmost 1.
        
        */
        if ((distance[cycle_start] == distance[cycle_end]) || (distance[cycle_start] - distance[cycle_end] == 1))
        {
            int w = cycle_start;
            if (distance[cycle_start] - distance[cycle_end] == 1)
            {
                
                w = parent[w];     // The distance of node cycle_start is 1 more.

                while (w != v)     // check till the common parent vertex is reached.
                {
                    cycle.push_back(w);
                    cycle_2.push_back(v);
                    v = parent[v];
                    w = parent[w];
                }
                cycle.push_back(w);
            }
            else // when both cycle_start and cycle_end node is at the same level.
            {
                while (w != v)
                {
                    cycle.push_back(v);
                    v = parent[v];
                    w = parent[w];
                    cycle_2.push_back(w);
                }
            }
            break;
        }
        
        cycle.push_back(v);
    }
    if (cycle_2.size() > 0) // when cross-edge in BFS is found.
    {
        reverse(cycle_2.begin(), cycle_2.end());
        cycle.insert(cycle.end(), cycle_2.begin(), cycle_2.end());
    }
    cycle.push_back(cycle_start);
    cout << cycle.size() << "\n";
    for (int v : cycle)
        cout << v << " ";
    return true;
}

int main() //driver code
{
    
    int n, m;
    cout << "Give n and m:"
         << "\n";
    cin >> n >> m; // Taking inputs
    Graph g(n);
    int a, b;
    for (int i = 0; i < m; i++)
    {
        cout << "Give a and b"
             << "\n";
        cin >> a >> b; //Taking inputs
        g.addEdge(a, b);
        g.addEdge(b, a);
    }
    if (!g.isCyclic())
        cout << "IMPOSSIBLE"
             << "\n";

    return 0;
}
