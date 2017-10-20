#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 1005;
const int INF = 1e9;
struct Edge {
  int from, to, cap, flow;
  Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f){}
};
struct Dinic {
  int m, s, t;
  vector<Edge>edges;
  vector<int>G[MAXN];
  bool vis[MAXN];
  int d[MAXN];
  int cur[MAXN];
  void AddEdge(int from, int to, int cap) {
    edges.push_back(Edge(from, to, cap, 0));
    edges.push_back(Edge(to, from, 0, 0));
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }
  bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int>Q;
    Q.push(s);
    d[s] = 0;
    vis[s] = 1;
    while(!Q.empty()) {
      int x = Q.front(); Q.pop();
      for(int i = 0; i < G[x].size(); i++) {
        Edge & e = edges[G[x][i]];
        if(!vis[e.to] && e.cap > e.flow) {
          vis[e.to] = true;
          d[e.to] = d[x]+1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }
  int DFS(int x, int a) {
    if(x == t || a == 0) return a;
    int flow = 0, f;
    for(int & i = cur[x]; i < G[x].size(); i++) {
      Edge & e = edges[G[x][i]];
      if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {  
        edges[G[x][i]].flow += f;
        edges[G[x][i] ^ 1].flow -= f;
        flow += f;
        a -= f;
        if(a == 0) break;
      }
    }
    return flow;
  }
  int Maxflow(int s, int t) {
    this->s = s, this->t = t;
    int flow = 0;
    while(BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }
};
struct MaxSubGraph {
  Dinic Flow;
  int val[MAXN], n;
  void init(int n) {
    this->n = n;
  }
  void AddEdge(int u, int v) {
    Flow.AddEdge(u, v, INF);
  }
  int solve() {
    if(!n) puts("need init.");
    int s = n + 1, t = n + 2;
    for(int i = 1; i <= n; i++) {
      if(val[i] > 0) {
        Flow.AddEdge(s, i, val[i]);
      } else {
        Flow.AddEdge(i, t, -val[i]);
      }
    }
    int res = -Flow.Maxflow(s, t);
    for(int i = 1; i <= n; i++) {
      if(val[i] > 0) {
        res += val[i];
      }
    }
    return res;
  }
};