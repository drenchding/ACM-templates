vector<int> e[MAXN], eInv[MAXN], bucket[MAXN];
int dfn[MAXN], id[MAXN], fa[MAXN], cur;
int idom[MAXN], sdom[MAXN];
int f[MAXN], val[MAXN];
int getVal(int i) {
  if(f[i] == i) return val[i];
  if(sdom[val[i]] > sdom[getVal(f[i])]) val[i] = val[f[i]];
  f[i] = f[f[i]];
  return val[i];
}
void dfs(int i) {
  sdom[i] = dfn[i] = ++cur; id[cur] = i;
  for(int j : e[i]) {
    if(!dfn[j]) {
      fa[j] = i; dfs(j);
    }
  }
}
//不可达 idom[i] = 0
void domTree(int n, int s) {
  for(int i = 1; i <= n; i++) {
    f[i] = i; 
    val[i] = dfn[i] = 0;
    bucket[i].clear();
  }
  idom[s] = fa[s] = 0; 
  sdom[0] = n;
  cur = 0; 
  dfs(s);
  for(int k = cur; k; k--) {
    int i = id[k];
    for(int j: eInv[i]) {
      if(dfn[j]) {
        sdom[i] = min(sdom[i], min(dfn[j], sdom[getVal(j)]));
      }
    }
    for(int j: bucket[i]) {
      int u = getVal(j);
      idom[j] = sdom[u] == sdom[j] ? sdom[j] : -u;
    }
    f[i] = fa[i]; 
    val[i] = i;
    bucket[id[sdom[i]]].push_back(i);
  }
  for(int k = 2; k <= cur; k++) {
    int & x = idom[id[k]];
    x = x > 0 ? id[x] : idom[-x];
  }
}