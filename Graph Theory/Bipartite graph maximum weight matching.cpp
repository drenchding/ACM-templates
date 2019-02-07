struct KM {
  int n, vis[MAXN], slack[MAXN], mat[MAXN], pre[MAXN];
  int g[MAXN][MAXN], ltag[MAXN], rtag[MAXN];
  void addEdge(int x, int y, int z) { // 左 -> 右
    g[y][x] = z;
  }
  void augment(int s) {
    for(int i = 0; i <= n; i++) 
      vis[i] = 0, slack[i] = INF;
    int v = 0, u; mat[v] = s;
    do {
      int a = INF, mn = 0;
      vis[v] = 1, u = mat[v];
      for(int i = 1; i <= n; i++) {
        if(vis[i]) continue;
        int t = ltag[u] + rtag[i] - g[u][i];
        if(t < slack[i]) slack[i] = t, pre[i] = v;
        if(slack[i] < a) a = slack[i], mn = i;
      }
      for(int i = 0; i <= n; i++) {
        if(vis[i]) ltag[mat[i]] -= a, rtag[i] += a; 
        else slack[i] -= a;
      }
      v = mn;
    } while(mat[v]);
    while(v) u = pre[v], mat[v] = mat[u], v = u;
  }
  long long solve(int nl, int nr) { // 左边人数、右边人数
    n = max(nl, nr);
    for(int i = 1; i <= n; i++) 
      for(int j = 1; j <= n; j++)
        ltag[i] = max(ltag[i], g[i][j]);
    for(int i = 1; i <= n; i++) augment(i);
    long long ans = 0;
    for(int i = 1; i <= n; i++) 
      ans += ltag[i] + rtag[i];
    /* mat[i] 表示左边第 i 个人和右边哪个匹配 */
    for(int i = 1; i <= nl; i++) 
      if(!g[mat[i]][i]) mat[i] = 0;
    return ans;
  }
};