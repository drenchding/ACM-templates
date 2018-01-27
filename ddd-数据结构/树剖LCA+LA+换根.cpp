#include <cstdio>
#include <vector>
#include <iostream>
 
using namespace std;
 
typedef long long ll;

const int MAXN = 300005;

int n, dfs_clock;
int fa[MAXN], deep[MAXN], size[MAXN], son[MAXN];
int dfn[MAXN], idfn[MAXN], low[MAXN], top[MAXN];

vector<int> G[MAXN];

namespace DS {
  ll c0[MAXN], c1[MAXN];
  void add(ll *c, int x, ll k) {
    for(; x <= n; x += x & -x) c[x] += k;
  }
  ll sum(ll *c, int x) { 
    ll r = 0; 
    for(; x; x -= x & -x) r += c[x];
    return r;
  }
  void add(int l, int r, ll k) {
    add(c0, l, k); add(c0, r + 1, -k);
    add(c1, l, (l - 1) * k); add(c1, r + 1, -r * k);
  }
  ll sum(int l, int r) {
    return sum(c0, r) * r - sum(c1, r) - sum(c0, l - 1) * (l - 1) + sum(c1, l - 1);
  }
}

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
  idfn[dfs_clock] = cur;
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
 
int LA(int cur, int dep) { // 求 cur 的深度为 dep 的祖先
  while(deep[top[cur]] > dep) cur = fa[top[cur]];
  return idfn[dfn[cur] + dep - deep[cur]];
}

bool contain(int u, int v) { // 判断 u 是否在 v 的子树内
  return dfn[u] >= dfn[v] && dfn[u] <= low[v];
}

int lca(int u, int v, int root) { // 求在以 root 为根的意义下，u 和 v 的 lca
  int z1 = lca(root, u);
  int z2 = lca(root, v);
  if(z1 == z2) return lca(u, v);
  return deep[z1] > deep[z2] ? z1 : z2;
}

void add(int cur, int x, int root) { // 在以 root 为根的意义下，对 cur 的子树加 x
  if(root == cur) DS::add(1, n, x);
  else if(contain(root, cur)) {
    DS::add(1, n, x);
    int t = LA(root, deep[cur] + 1);
    DS::add(dfn[t], low[t], -x);
  } else {
    DS::add(dfn[cur], low[cur], x);
  }
}

ll query(int cur, int root) { // 在以 root 为根的意义下，求 cur 的子树和
  ll res = 0;
  if(root == cur) res = DS::sum(1, n);
  else if(contain(root, cur)) {
    res += DS::sum(1, n);
    int t = LA(root, deep[cur] + 1);
    res -= DS::sum(dfn[t], low[t]);
  } else {
    res = DS::sum(dfn[cur], low[cur]);
  }
  return res;
}

int main() {
  return 0;
}