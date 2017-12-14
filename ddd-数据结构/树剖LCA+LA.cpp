#include <cstdio>
#include <vector>
#include <iostream>
 
using namespace std;
 
const int MAXN = 300005;
 
int dfs_clock;
int fa[MAXN], deep[MAXN], size[MAXN], son[MAXN], top[MAXN];
int dfn[MAXN], dfm[MAXN], low[MAXN];
 
vector<int> G[MAXN];
 
void addEdge(int x, int y) {
  G[x].push_back(y);
  G[y].push_back(x);
}
 
void dfs1(int cur, int father, int dep) {
  fa[cur] = father;
  deep[cur] = dep;
  size[cur] = 1;
  son[cur] = 0;
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i];
    if(nx != father) {
      dfs1(nx, cur, dep + 1);
      size[cur] += size[nx];
      if(size[nx] > size[son[cur]]) {
        son[cur] = nx;
      }
    }
  }
}
 
void dfs2(int cur, int tp) {
  top[cur] = tp;
  dfn[cur] = ++dfs_clock;
  dfm[dfs_clock] = cur;
  if(son[cur]) dfs2(son[cur], tp);
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i];
    if(nx != fa[cur] && nx != son[cur]) {
      dfs2(nx, nx);
    }
  }
  low[cur] = dfs_clock;
}
 
int lca(int x, int y) {
  int t1 = top[x], t2 = top[y];
  while(t1 != t2) {
    if(deep[t1] < deep[t2]) {
      swap(t1, t2);
      swap(x, y);
    }
    x = fa[t1], t1 = top[x];
  }
  return deep[x] < deep[y] ? x : y;
}
 
int LA(int cur, int dep) {
  if(deep[cur] < dep) return -1;
  while(deep[top[cur]] > dep) cur = fa[top[cur]];
  return dfm[dfn[cur] + dep - deep[cur]];
}