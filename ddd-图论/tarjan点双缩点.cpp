void tarjan(int x) {
  dfn[x] = low[x] = ++dfs_clock;
  vis[x] = 1; stack[++top] = x;
  for(int i = 0; i < G[x].size(); i++) {
    int nx = G[x][i];
    if(!dfn[nx]) {
      tarjan(nx);
      low[x] = min(low[x], low[nx]);
      if(dfn[x] <= low[nx]) {
        int now = 0; ++bcc_cnt;
        while(now != nx) {
          now = stack[top--];
          vis[now] = 0;
          addEdge(bcc_cnt + n, now);
        }
        addEdge(bcc_cnt + n, x);
      }
    } else if(vis[nx]) {
      low[x] = min(low[x], dfn[nx]);
    }
  }
}