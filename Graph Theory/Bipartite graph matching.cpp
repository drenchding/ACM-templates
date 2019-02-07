struct Edge { int v, n; } e[MAXM];
struct Hungarian {
  int tot, tm, ans, s[MAXM], mat[MAXM], vis[MAXM];
  void clear() {
    tot = tm = ans = 0;
    memset(s, 0, sizeof(s));
    memset(mat, 0, sizeof(mat));
    memset(vis, 0, sizeof(vis));
  }
  void addEdge(int u, int v) { // 左 -> 右
    e[++tot] = (Edge){u, s[v]};
    s[v] = tot;
  }
  bool dfs(int u) {
    for(int i = s[u]; i; i = e[i].n) 
      if(vis[e[i].v] < tm) {
        vis[e[i].v] = tm;
        if((!mat[e[i].v]) || dfs(mat[e[i].v])) {
          mat[e[i].v] = u; return 1;
        }
      }
    return 0;
  }
  void find(int st) { tm++; if(dfs(st)) ans++; }
  int solve(int n, int m) { // 左边人数、右边人数
    for(int i = 1; i <= m; i++) find(i);
    /* mat[i] 表示左边第 i 个人和右边哪个人匹配 */
    return ans; 
  }
};