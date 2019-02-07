vector<int> G[MAXN];
int ind[MAXN];

void addEdge(int x, int y) {
  G[x].push_back(y);
  ++ind[y];
}

vector<int> getTopo() {
  queue<int> Q;
  for(int i = 1; i <= n; i++) {
    if(!ind[i]) {
      Q.push(i);
    }
  }
  vector<int> ans;
  while(!Q.empty()) {
    int cur = Q.front(); Q.pop();
    ans.push_back(cur);
    for(auto nx: G[cur]) {
      --ind[nx];
      if(!ind[nx]) {
        Q.push(nx);
      }
    }
  }
  return ans;
}