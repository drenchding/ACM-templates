vector<int> G[MAXN];
vector<int> G2[MAXN];
namespace SCC {
  stack<int> S;
  vector<int> SCC[MAXN];
  int cnt, tot;
  int dfn[MAXN], low[MAXN], fa[MAXN];
  bool vis[MAXN], instack[MAXN];
  void tarjan(int cur) {
    S.push(cur);
    dfn[cur] = low[cur] = ++cnt;
    vis[cur] = instack[cur] = 1;
    for(int i = 0; i < G[cur].size(); i++) {
      int nx = G[cur][i];
      if(!vis[nx]) {
        tarjan(nx);
        low[cur] = min(low[cur], low[nx]);
      } else if(instack[nx]) {
        low[cur] = min(low[cur], dfn[nx]);
      }
    }
    if(dfn[cur] == low[cur]) {
      tot++;
      int tp;
      do {
        tp = S.top(); S.pop();
        instack[tp] = 0;
        fa[tp] = tot;
        SCC[tot].push_back(tp);
      } while(tp != cur);
    }
  }
  void getNewGraph() {
    for(int i = 1; i <= n; i++) {
      if(!vis[i]) tarjan(i);
    }
    for(int i = 1; i <= n; i++) {
      int x = i;
      for(int j = 0; j < G[i].size(); j++) {
        int y = G[i][j];
        if(fa[x] != fa[y]) {
          G2[fa[x]].push_back(fa[y]);
        }
      }
    }
  }
}
