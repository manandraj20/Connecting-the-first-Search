#include <bits/stdc++.h>
using namespace std;
class Solution{
    public:
void topsort(vector<vector<int>> &adj,int V){
    
    vector<int> in_degree(V, 0);
    for(int u=0;u<V;u++){
     vector<int>::iterator itr;
        for (itr = adj[u].begin();
             itr != adj[u].end(); itr++)
            in_degree[*itr]++;
    }
       queue<int> q;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            q.push(i);
            
    int cnt=0;
    vector<int> top_order;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        top_order.push_back(u);
        vector<int>::iterator itr;
        for (itr = adj[u].begin();
             itr != adj[u].end(); itr++)
 
            // If in-degree becomes zero,
            // add it to queue
            if (--in_degree[*itr] == 0)
                q.push(*itr);
 
        cnt++;
    }
    if (cnt != V) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (int i = 0; i < top_order.size(); i++)
        cout << top_order[i]+1 << " ";
    cout << endl;
    return;
}
};

int main() {
	// your code goes here
	int n, m;
	cin>>n>>m;
	int a,b;
	vector<vector<int>> adj(n);
	while(m--){
	    cin>>a>>b;
	    adj[a-1].push_back(b-1);
	    
	}
	
	Solution solver;
	
	solver.topsort(adj, n);
	
	
	return 0;
}
