import java.util.*;
public class Test {

  public static void main(String[] args) {
    new Test(new Scanner(System.in));
  }

  Graph g;
  int[] pre, low;
  ArrayList<Integer> to_be_deleted;
  boolean[] art;
  int cnt = 0;

  int dfs(int i, int p, int id) {
    if (pre[i] != -1) {
      low[p] = Math.min(low[p], pre[i]);
      return low[p];
    }
    pre[i] = cnt++;
    low[i] = pre[i];
    boolean hasFwd = false;
    for (Edge e : g.adj[i]) {
		
      if (e.id == id) {
        continue;
      }
      if (dfs(e.j, i, e.id) < 0) {
        low[i] = Math.min(low[i], low[e.j]);
        if (low[e.j] == pre[e.j]) {
          to_be_deleted.add(e.j);
        }
        if (i != p ? low[e.j] >= pre[i] : hasFwd) {
          art[i] = true;
        }
        hasFwd = true;
      }
    }

    return -1;
  }
  Test(Scanner in)
  {
      g= new Graph(in.nextInt());
      int M= in.nextInt();
      while(M-->0)
      {
          int i= in.nextInt()-1;
          int j= in.nextInt()-1;
          g.add(i, j);

      }
      pre= new int[g.N];
      low= new int[g.N];
      Arrays.fill(pre, -1);
      to_be_deleted= new ArrayList<>();
      art = new boolean [g.N];
      for(int i=0; i<g.N; i++)
      {
          if(pre[i]==-1)
          {
              dfs(i, i, g.M);
          }
      }
      System.out.printf("Bridges are %s%n", to_be_deleted);
      System.out.println("--------------");
      ArrayList<Integer> arts= new ArrayList<>();
      for(int i=0;i<g.N;i++)
      {
          if(art[i])
          {
              arts.add(i);
          }
      }
      System.out.printf("Articulation points are : %s", arts);
  }
  class Graph{
      int N, M;
      ArrayList<Edge> []adj;
	  Graph (int NN)
	  {
		  M=0;
		  adj= new ArrayList[N=NN];
		  for(int i=0;i< N; i++)
		  {
			  adj[i]= new ArrayList<>();
		  }
	  }
	  void add(int i, int j)
	  {
		  adj[i].add(new Edge(j, M));
		  adj[j].add(new Edge(i, M));
		  M++;
	  }
     
  }
  class Edge{
      int j, id;
      Edge(int jj, int ii)
      {
          j=jj; id=ii;
      }
  }
}
