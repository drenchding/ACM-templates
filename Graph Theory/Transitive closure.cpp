int vis[MAXN];
bitset<MAXN> reach[MAXN];
vector<int> G[MAXN]; // G 是一个 DAG
void dfs(int cur) { // 对所有入度为 0 的点使用
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i];
    if(!vis[nx]) {
      vis[nx] = 1;
      dfs(nx);
    }
    reach[cur][nx] = 1;
    reach[cur] |= reach[nx];
  }
}
void addEdge(int u, int v) {
  G[u].push_back(v);
  reach[u][v] = 1;
}
