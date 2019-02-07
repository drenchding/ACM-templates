const int MAXN = 5005;
const int INF = 1 << 30;
struct Edge {
  int from, to, cap, flow, cost;
  Edge(int u, int v, int c, int f, int w) : from(u), to(v), cap(c), flow(f), cost(w){}
};
struct MCMF {
  int m;
  vector<Edge>edges;
  vector<int>G[MAXN];
  int inq[MAXN], p[MAXN], a[MAXN], d[MAXN];
  void addEdge(int from, int to, int cap, int cost) {
    edges.push_back(Edge(from, to, cap, 0, cost));
    edges.push_back(Edge(to, from, 0, 0, -cost));
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }
  bool spfa(int s, int t, int & flow, ll & cost) {
    memset(d, 127, sizeof(d));
    memset(inq, 0, sizeof(inq));
    d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;
    queue<int>Q; Q.push(s);
    while(!Q.empty()) {
      int u = Q.front(); Q.pop();
      inq[u] = 0;
      for(int i = 0; i < G[u].size(); i++) {
        Edge & e = edges[G[u][i]];
        if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
          d[e.to] = d[u] + e.cost;
          p[e.to] = G[u][i];
          a[e.to] = min(a[u], e.cap - e.flow);
          if(!inq[e.to]) {
            Q.push(e.to);
            inq[e.to] = 1;
          }
        }
      }
    }
    if(d[t] >= INF) return false;
    flow += a[t];
    cost += (ll)d[t] * (ll)a[t];
    for(int u = t; u != s; u = edges[p[u]].from) {
      edges[p[u]].flow += a[t];
      edges[p[u] ^ 1].flow -= a[t];
    }
    return true;
  }
  int MincostMaxflow(int s, int t, ll & cost) {
    int flow = 0; cost = 0;
    while(spfa(s, t, flow, cost));
    return flow;
  }
};
