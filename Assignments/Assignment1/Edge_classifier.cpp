#include <bits/stdc++.h>
using namespace std;

vector<bool> visited;

int dfs_timer = 0;
map<pair<int, int>, int> edge_classified;
string Edge_classifier(pair<int, int> Edge)
{
  return edge_classified[Edge] == 1 ? "Tree_Edge" : "Backward_edge";
}

void dfs(int v, vector<vector<int>> &adj, vector<int> &time_in, vector<int> &time_out, int par)
{
  time_in[v] = dfs_timer++;
  visited[v] = true;
  for (int u : adj[v])
  {
    pair<int, int> edge_1 = make_pair(v, u);
    pair<int, int> edge_2 = make_pair(u, v);
    if (!visited[u])
    {
      dfs(u, adj, time_in, time_out, v);

      edge_classified[edge_1] = 1;
      edge_classified[edge_2] = 1;
    }
    else if (u == par)
    {
      continue;
    }
    else
    {
      edge_classified[edge_1] = 0;
      edge_classified[edge_2] = 0;
    }
  }

  time_out[v] = dfs_timer++;
}
int main()
{
  int n;
  int m;
  cin >> n >> m;
  int a, b;
  for (int i = 0; i < n; i++)
  {
    visited.push_back(false);
  }
  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < m; i++)
  {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<int> time_out(n);
  vector<int> time_in(n);

  for (int i = 0; i < n; i++)
  {
    if (!visited[i])
      dfs(i, adj, time_in, time_out, -1);
  }
  cout << Edge_classifier(make_pair(0, 2));
  return 0;
}