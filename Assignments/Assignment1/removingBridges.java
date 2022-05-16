import java.util.*;

public class Test {

  public static void main(String[] args) {
    new Test(new Scanner(System.in));
  }

  Graph g;
  int[] pre, low, par;
  ArrayList<Integer> to_be_deleted;
  int cnt = 0;

  void dfs(int i) {
    pre[i] = cnt++;
    low[i] = pre[i];
    for (int e : g.adj[i]) {
      if (par[i] == e) {
        continue;
      } else if (pre[e] != -1) {
        low[i] = Math.min(low[i], pre[e]); //Back edge
      } else { // Tree Edge
        par[e]=i;
        dfs(e);
        low[i] = Math.min(low[i], low[e]);
        if (low[e] == pre[e]) {
          
          to_be_deleted.add(e);
        }
      }
    }
  }

  Test(Scanner in) {
    g = new Graph(in.nextInt());
    int M = in.nextInt();
    while (M-- > 0) {
      int i = in.nextInt() ;
      int j = in.nextInt() ;
      g.add(i, j);
    }
    pre = new int[g.N];
    low = new int[g.N];
    par = new int[g.N];
    Arrays.fill(par, -1);
    Arrays.fill(pre, -1);
    to_be_deleted = new ArrayList<>();
    // art = new boolean[g.N];
    for (int i = 0; i < g.N; i++) {
      if (pre[i] == -1) {
        dfs(i);
      }
    }
   
    Iterator itr = to_be_deleted.iterator();
    while(itr.hasNext()){
        int x = (Integer)itr.next();
        int p= par[x];
        g.adj[p].remove(new Integer(x));
        g.adj[x].remove(new Integer(p));
    }

    
  }

  class Graph {

    int N;
    ArrayList<Integer>[] adj;

    Graph(int NN) {
      adj = new ArrayList[N = NN];
      for (int i = 0; i < N; i++) {
        adj[i] = new ArrayList<>();
      }
    }

    void add(int i, int j) {
      adj[i].add(j);
      adj[j].add(i);
    }
  }
}

