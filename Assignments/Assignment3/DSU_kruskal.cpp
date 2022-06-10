#include <bits/stdc++.h>
using namespace std;
class DSU
{
    int n;
    vector<int> par;
    vector<int> rank;
    vector<int> size;

public:
    DSU(int NN)
    {
        this->n = NN;
        this->par = vector<int>(n, -1);
        this->rank = vector<int>(n, -1);
        this->size = vector<int>(n, 0);
        for (int u = 0; u < n;)
        {
            make_set(u);
            u++;
        }
    }
    void make_set(int u)
    {
        par[u] = u;
        rank[u] = 0;
        size[u] = 1;
    }
    int find_set(int u)
    {
        if (u == par[u])
        {
            return u;
        }
        return par[u] = find_set(par[u]);
    }
    void union_set(int u, int v)
    {
        int u_id = find_set(u);
        int v_id = find_set(v);
        if (u_id != v_id)
        {
            if (rank[u_id] < rank[v_id])
            {
                int temp = u_id;
                u_id = v_id;
                v_id = temp;
            }
            par[v_id] = u_id;
            if (rank[u_id] == rank[v_id])
            {
                rank[u_id]++;
            }
        }
    }
};
struct Edge

{
    int u, v;
    int wt;
    bool operator<(Edge const &other)
    {
        return wt < other.wt;
    }
};
class Kruskal_Tree
{
    int nNodes;
    int nEdges;
    DSU dsu;
    vector<Edge> result;
    vector<Edge> edgesList;

public:
    Kruskal_Tree(int NN, int M) : dsu(NN)
    {
        this->dsu = DSU(NN);
        this->nNodes = NN;
        this->nEdges = M;
        edgesList = vector<Edge>(M);
    }
    void addEdge(int u, int v, int wt)
    {
        Edge edge = {u, v, wt};
        edgesList.push_back(edge);
    }
    long long minSpanningTreeWt()
    {
        long long minWt = 0;
        sort(edgesList.begin(), edgesList.end());
        for (Edge edge : edgesList)
        {
            int u = edge.u;
            int v = edge.v;
            int wt = edge.wt;
            if (dsu.find_set(u) != dsu.find_set(v))
            {
                minWt += (long long)wt;
                result.push_back(edge);
                dsu.union_set(u, v);
            }
        }
        return minWt;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    int u, v, wt;
    // DSU Dsu(n);
    Kruskal_Tree kt(n, m);
    while (m--)
    {
        cin >> u >> v >> wt;

        kt.addEdge(u - 1, v - 1, wt);
    }
    long long res = kt.minSpanningTreeWt();
    cout << res;
    return 0;
}