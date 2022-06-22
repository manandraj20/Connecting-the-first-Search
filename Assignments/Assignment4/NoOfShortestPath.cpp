// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include<bits/stdc++.h>
using namespace std;
# define INF 1e18LL
#define M 1000000007

// iPair ==> Integer Pair
typedef pair<long long, int> iPair;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
	int V; // No. of vertices

	// In a weighted graph, we need to store vertex
	// and weight pair for every edge
	list< pair<long long, int> > *adj;

public:
	Graph(int V); // Constructor

	// function to add an edge to graph
	void addEdge(int u, int v, int w);

	// prints shortest path from s
	void shortestPath(int s);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<iPair> [V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
// 	adj[v].push_back(make_pair(u, w));
}

// Prints shortest paths from src to all other vertices
void Graph::shortestPath(int src)
{
	// Create a priority queue to store vertices that
	// are being preprocessed. This is weird syntax in C++.
	// Refer below link for details of this syntax
	// https://www.geeksforgeeks.org/implement-min-heap-using-stl/
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

	// Create a vector for distances and initialize all
	// distances as infinite (INF)
	vector<long long> dist(V, INF);
	vector<int> totalWays(V,0);
	vector<int> mnmFlight(V, INF);
	vector<int> mxmFlight(V,0);
	totalWays[src]=1;
	mxmFlight[src]=mnmFlight[src]=0;

	// Insert source itself in priority queue and initialize
	// its distance as 0.
	pq.push(make_pair(0, src));
	dist[src] = 0;

	/* Looping till priority queue becomes empty (or all
	distances are not finalized) */
	while (!pq.empty())
	{
		// The first vertex in pair is the minimum distance
		// vertex, extract it from priority queue.
		// vertex label is stored in second of pair (it
		// has to be done this way to keep the vertices
		// sorted distance (distance must be first item
		// in pair)
		int u = pq.top().second;
        long long w=pq.top().first;
        
		pq.pop();
        if(dist[u]<w) continue;


		// 'i' is used to get all adjacent vertices of a vertex
		list< pair<long long, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			// Get vertex label and weight of current adjacent
			// of u.
			int v = (*i).first;
			int weight = (*i).second;

			// If there is shorted path to v through u.
			if (dist[v] == dist[u] + weight)
			{
				// Updating distance of v
				// dist[v] = dist[u] + weight;
				totalWays[v]=(totalWays[v]%M+totalWays[u]%M)%M;
				mnmFlight[v]= min(mnmFlight[v], mnmFlight[u]+1);
				mxmFlight[v]=max(mxmFlight[v], mxmFlight[u]+1);
				// pq.push(make_pair(dist[v], v));
				
			}
			else if (dist[v] >dist[u] + weight)
			{
				// Updating distance of v
				dist[v] = dist[u] + weight;
				totalWays[v]=totalWays[u]%M;
				mxmFlight[v]=mxmFlight[u]+1;
				mnmFlight[v]=mnmFlight[u]+1;
				pq.push(make_pair(dist[v], v));
				
			}
			
		}
	}

	// Print shortest distances stored in dist[]
// 	printf("Vertex Distance from Source\n");
// 	for (int i = 0; i < V; ++i)
// 		printf("%d \t\t %d \t %d \t %d \t %d\n", i, dist[i], totalWays[i], mxmFlight[i], mnmFlight[i]);
cout<<dist[V-1]<<" "<<totalWays[V-1]<<" "<<mnmFlight[V-1]<<" "<<mxmFlight[V-1]<<endl;
}

// Driver program to test methods of graph class
int main()
{
	// create the graph given in above figure
// 	int V = 5;
// 	Graph g(V);
int n, m;
cin>>n;
Graph g(n);
cin>>m;
int a, b, c;
while(m--){
    cin>>a>>b>>c;
    g.addEdge(a-1, b-1, c);
}
	// making above shown graph
	
// 	g.addEdge(5, 3, 1);
	

	g.shortestPath(0);

	return 0;
}
