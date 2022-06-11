#include <bits/stdc++.h>
using namespace std;
class DSU
{
    int n;
    vector<int> par;
    vector<int> rank;

public:
    DSU(int c)
    {
        n = c;

        par = vector<int>(n, -1);
        rank = vector<int>(n, -1);

        for (int i = 0; i < n; i++)
        {
            make_set(i);
        }
    }

    void make_set(int v)
    {
        par[v] = v;
        rank[v] = 0;
    }
    int find_set(int v)
    {
        if (v == par[v])
        {
            return v;
        }
        return par[v] = find_set(par[v]);
    }
    void union_set(int u, int v)
    {
        int a = find_set(u);
        int b = find_set(v);
        if (a != b)
        {
            if (rank[a] < rank[b])
            {
                int temp = a;
                a = b;
                b = temp;
            }
            par[b] = a;
            if (rank[b] == rank[a])
            {
                rank[a]++;
            }
        }
    }
};

int main()
{
    // your code goes here
    int n, m;
    cin >> n >> m;

    string input;
    string token;

    DSU solver(n);
    int flag = 0;
    int u = -1;
    int v;
    getline(cin, input);

    while (m--)
    {
        input = "";

        getline(cin, input);

        stringstream ss(input);
        while (getline(ss, token, ' '))
        {

            if (token == "union")
            {
                flag = 1;
            }
            else if (token == "get")
            {
                flag = 0;
            }
            else
            {
                if (u == -1)
                    u = stoi(token);
                else
                {
                    v = stoi(token);
                }
            }
        }

        if (flag == 1)
        {
            solver.union_set(u - 1, v - 1);
        }
        else
        {
            int u_par = solver.find_set(u - 1);
            int v_par = solver.find_set(v - 1);
            if (u_par == v_par)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
        u = -1;
    }

    return 0;
}
