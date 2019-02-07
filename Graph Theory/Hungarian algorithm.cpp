namespace Hungarian {
  const int MAXM = 250005;
  struct Edge {
    int v, n;
  }e[MAXM];
  int s[MAXM], mat[MAXM], vis[MAXM];
  int tot, tm, ans;
  void clear() {
    memset(s, 0, sizeof(s));
    memset(mat, 0, sizeof(mat));
    memset(vis, 0, sizeof(vis));
    tot = tm = ans = 0;
  }
  inline void addEdge(int u, int v) {
    e[++tot] = (Edge){v, s[u]};
    s[u] = tot;
  }
  bool dfs(int u) {
    for(int i = s[u]; i; i = e[i].n) if(vis[e[i].v] < tm) {
      vis[e[i].v] = tm;
      if((!mat[e[i].v]) || dfs(mat[e[i].v])) {
        mat[e[i].v] = u; return 1;
      }
    }
    return 0;
  }
  inline void find(int st) {
    tm++; if(dfs(st)) ans++;
  }
  void solve(int n, int m) { // left: [1, n]，right: [1, m]，Edge: left -> right
    for(int i = 1; i <= n; i++) find(i);
    printf("%d\n", ans);
    // mat[i] 表示右边第 i 个人和左边哪个人匹配
    for(int i = 1; i <= m; i++) printf("%d ", mat[i]); 
  }
}