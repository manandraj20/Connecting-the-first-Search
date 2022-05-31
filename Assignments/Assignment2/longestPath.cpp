#include <bits/stdc++.h>
using namespace std;
class Solution{
    public:
vector<int> topsort(vector<vector<int>> &adj,int V){
    
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
    
   
    return top_order;
}

vector<int> dagLongestPath(vector<vector<int>> &adj, int V, int start, int last){
    vector<int> top_order= topsort(adj, V);
   vector<int> dist(V,-1);
    // for(auto ele: top_order){
    //     cout<<ele+1<<" ";
    // }
    cout<<endl;
    
    vector<int> whoIsBack(V,-1);
    dist[start]=0;
    for(int i=0;i<V;i++){
        int nodeIndex= top_order[i];
        if(dist[nodeIndex]!=-1){
            vector<int> adjacentEdges= adj[nodeIndex];
            if(!adjacentEdges.empty()){
                for(auto ele: adjacentEdges){
                    int newDist= dist[nodeIndex]+1;
                    if(newDist> dist[ele]){
                        dist[ele]=newDist;
                        whoIsBack[ele]=nodeIndex;
                    }
                }
            }
            
        }
    }
    if(dist[V-1]==-1) cout<<"IMPOSSIBLE\n";
    else{
        cout<<dist[V-1]+1<<endl;
    }
    
    return whoIsBack;
    
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
	
	vector<int> whoIsBack=solver.dagLongestPath(adj, n,0,n-1);
// 	for(auto ele: final){
// 	    cout<<ele+1<<" ";
// 	}
	vector<int> to_be_printed;

	to_be_printed.push_back(n-1);
	if(whoIsBack[n-1]==-1) ;
	else{
	   
	    int index=n-1;
	    while(whoIsBack[index]!=-1){
	        to_be_printed.push_back(whoIsBack[index]);
	        index=whoIsBack[index];
	    }
	    for(auto it=to_be_printed.rbegin();it!=to_be_printed.rend();it++){
	        cout<<(*it)+1<<" ";
	    }
	    
	}
	cout<<endl;
	
	
	return 0;
}
