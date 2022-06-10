import java.io.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {

  public static void main(String[] args) {
    InputStream inputStream = System.in;
    OutputStream outputStream = System.out;
    InputReader in = new InputReader(inputStream);
    PrintWriter out = new PrintWriter(outputStream);
    TaskA solver = H(1, in, out);

    out.close();
  }
}

public class H {

  public H(int tc, FastScanner in, PrintWriter out) {
    Graph g = new Graph(in.nextInt()); //taking the number of nodes in the graph
    int M = in.nextInt(); //taking the number of edges
    while (
      M-- > 0
    ) { //scanning every edge
      int i = in.nextInt() - 1;
      int j = in.nextInt() - 1;
      g.add(i, j); //adding current edge to the graph
    }

    Tarjan scc = new Tarjan(g); // calling Tarjan on the graph

    //       if (scc.numSCCs == 1)
    //          out.println(0);
    //       else
    //       {
    //          int[] indeg = new int[scc.numSCCs];
    //          int[] outdeg = new int[scc.numSCCs];

    //          for (int i=0; i<g.N; i++)
    //             for (int j : g.adj[i])
    //                if (scc.id[i] != scc.id[j])
    //                {
    //                   outdeg[scc.id[i]]++;
    //                   indeg[scc.id[j]]++;
    //                }

    //          int numSrcs = 0;
    //          int numSnks = 0;
    //          for (int i=0; i<scc.numSCCs; i++)
    //          {
    //             if (indeg[i] == 0)
    //                numSrcs++;
    //             if (outdeg[i] == 0)
    //                numSnks++;
    //          }
    //          out.println(Math.max(numSrcs, numSnks));
    //       }

    //       Graph meta = new Graph(scc.numSCCs);
    //       for (int i=0; i<g.N; i++)
    //          for (int j : g.adj[i])
    //             if (scc.id[i] != scc.id[j])
    //                meta.add(scc.id[i], scc.id[j]);
    //    }
    for (int currComp = 0; currComp < scc.numSCCs; currComp++) {
      out.printf("%d: ", currComp + 1);
      for (int i = 0; i < g.N; i++) {
        if (scc.id[i] == currComp) {
          out.printf("%d ", i + 1);
        }
      }
      out.println();
    }
  }
}

class Tarjan {

  Graph g;
  int[] pre; //order of traversing the graph or t_in time
  int[] id; //id to denote the strongly connected component a node belongs to
  int[] low; // low link value
  ArrayDeque<Integer> stk;
  int preorderCounter;
  int numSCCs;

  Tarjan(Graph gg) {
    g = gg;
    stk = new ArrayDeque<>();
    pre = new int[g.N];
    id = new int[g.N];
    low = new int[g.N];

    numSCCs = 0;
    preorderCounter = 0;
    Arrays.fill(pre, -1);

    for (int i = 0; i < g.N; i++) if (pre[i] == -1) dfs(i);
  }

  void dfs(int i) {
    pre[i] = preorderCounter++;
    low[i] = pre[i];
    stk.push(i);

    for (int j : g.adj[i]) {
      if (pre[j] == -1) dfs(j);
      //Fwd, backward and cross edge case
      low[i] = Math.min(low[i], low[j]); // taking min with the low link of children ; here we have taken low with low of children even in the case
      //of backward edge this is true as we are dealing with bridges and not articulation points here
    }

    // Are we root of the SCC?
    if (low[i] == pre[i]) {
      System.out.println(stk);
      while (true) {
        int j = stk.pop();
        id[j] = numSCCs;
        low[j] = g.N; //setting the low link value high enough that cross edges update is eliminated

        if (
          i == j
        ) break; // when you hit the node which started the scc then break
      }
      numSCCs++;
    }
  }
}

class Graph {

  int N;
  ArrayList<Integer>[] adj;

  Graph(int NN) {
    adj = new ArrayList[N = NN];
    for (int i = 0; i < N; i++) adj[i] = new ArrayList<>();
  }

  void add(int i, int j) {
    adj[i].add(j);
  }
}

class FastScanner {

  private InputStream stream;
  private byte[] buf = new byte[1024];
  private int curChar;
  private int numChars;

  public FastScanner(InputStream stream) {
    this.stream = stream;
  }

  int read() {
    if (numChars == -1) throw new InputMismatchException();
    if (curChar >= numChars) {
      curChar = 0;
      try {
        numChars = stream.read(buf);
      } catch (IOException e) {
        throw new InputMismatchException();
      }
      if (numChars <= 0) return -1;
    }
    return buf[curChar++];
  }

  boolean isSpaceChar(int c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
  }

  boolean isEndline(int c) {
    return c == '\n' || c == '\r' || c == -1;
  }

  int nextInt() {
    return Integer.parseInt(next());
  }

  long nextLong() {
    return Long.parseLong(next());
  }

  double nextDouble() {
    return Double.parseDouble(next());
  }

  String next() {
    int c = read();
    while (isSpaceChar(c)) c = read();
    StringBuilder res = new StringBuilder();
    do {
      res.appendCodePoint(c);
      c = read();
    } while (!isSpaceChar(c));
    return res.toString();
  }

  String nextLine() {
    int c = read();
    while (isEndline(c)) c = read();
    StringBuilder res = new StringBuilder();
    do {
      res.appendCodePoint(c);
      c = read();
    } while (!isEndline(c));
    return res.toString();
  }
}
