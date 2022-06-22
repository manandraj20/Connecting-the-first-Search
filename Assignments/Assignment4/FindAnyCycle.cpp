#include <bits/stdc++.h>
using namespace std;
struct Edge
{
	int a, b; int cost;
};

int n, m;
vector<Edge> edges;
// const int INF = 1000000000;

void solve()
{
	cin >> n >> m;
	int ai, bi, c;
	while (m--)
	{
		cin >> ai >> bi >> c;
		struct Edge e = {ai-1, bi-1, c};
		edges.push_back(e);
	}
	vector<long long> d(n, 0);
	vector<int> p(n, -1);
	int x;
	for (int i = 0; i < n; ++i)
	{
		x = -1;
		for (struct Edge e : edges)
		{
			if (d[e.a] + e.cost < d[e.b])
			{
				d[e.b] = d[e.a] + e.cost;
				p[e.b] = e.a;
				x = e.b;
			}
		}
	}

	if (x == -1)
	{
		cout << "NO\n";
	}
	else
	{
		for (int i = 0; i < n; ++i)
			x = p[x];

		vector<int> cycle;
		for (int v = x;; v = p[v])
		{
			cycle.push_back(v);
			if (v == x && cycle.size() > 1)
				break;
		}
    
		reverse(cycle.begin(), cycle.end());

		cout << "YES\n";
		for (int v : cycle)
			cout << v+1<< ' ';
		cout << endl;
	}
}

int main()
{
	solve();
	return 0;
}