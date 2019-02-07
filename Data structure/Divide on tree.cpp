void getroot(int cur, int fa) {
  size[cur] = 1;
  f[cur] = 0;
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i];
    if(nx == fa || vis[nx]) {
      continue;
    }
    getroot(nx, cur);
    size[cur] += size[nx];
    f[cur] = max(f[cur], size[nx]);
  } 
  f[cur] = max(f[cur], sz - f[cur]);
  if(f[cur] < f[root]) root = cur;
}
void cal(int cur) {
  // 统计以 cur 为根的子树中，所有经过 cur 的路径的信息
}
void solve(int cur) {
  vis[cur] = 1;
  cal(cur);
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i];
    if(vis[nx]) continue;
    f[0] = sz = size[nx];
    getroot(nx, root = 0);
    solve(root);
  }
}
void work() {
  f[0] = sz = n;
  getroot(1, root = 0);
  solve(root);
}
