// 树链 mex
#include <bits/stdc++.h>
using namespace std;
const int MAXV = 200010;
const int MAXE = MAXV << 1;
const int MAXQ = 200010;
const int MLOG = 22;
int n, m;
int head[MAXV], val[MAXV], ecnt;
int to[MAXE], next[MAXE];
int stk[MAXV], top;
int block[MAXV], bcnt, bsize;
struct Query {
  int u, v, id;
  void read(int i) {
    id = i;
    scanf("%d%d", &u, &v);
  }
  void adjust() {
    if(block[u] > block[v]) swap(u, v);
  }
  bool operator < (const Query &rhs) const {
    if(block[u] != block[rhs.u]) return block[u] < block[rhs.u];
    return block[v] < block[rhs.v];
  }
} ask[MAXQ];
int ans[MAXQ];
void init() {
  memset(head + 1, -1, n * sizeof(int));
  ecnt = 0;
}
void add_edge(int u, int v) {
  to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
  to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}
void read() {
  scanf("%d", &n); init();
  for(int i = 1, u, v; i < n; ++i) {
    scanf("%d%d", &u, &v);
    add_edge(u, v);
  }
  for(int i = 1; i <= n; ++i) scanf("%d", &val[i]);
  scanf("%d", &m);
  for(int i = 0; i < m; ++i) ask[i].read(i);
}
void add_block(int &cnt) {
  while(cnt--) block[stk[--top]] = bcnt;
  bcnt++;
  cnt = 0;
}
void rest_block() {
  while(top) block[stk[--top]] = bcnt - 1;
}
int dfs_block(int u, int f) {
  int size = 0;
  for(int p = head[u]; ~p; p = next[p]) {
    int v = to[p];
    if(v == f) continue;
    size += dfs_block(v, u);
    if(size >= bsize) add_block(size);
  }
  stk[top++] = u;
  size++;
  if(size >= bsize) add_block(size);
  return size;
}
void init_block() {
  bsize = max(1, (int)sqrt(n));
  dfs_block(1, 0);
  rest_block();
}
int fa[MLOG][MAXV];
int dep[MAXV];
void dfs_lca(int u, int f, int depth) {
  dep[u] = depth;
  fa[0][u] = f;
  for(int p = head[u]; ~p; p = next[p]) {
    int v = to[p];
    if(v != f) dfs_lca(v, u, depth + 1);
  }
}
void init_lca() {
  dfs_lca(1, -1, 0);
  for(int k = 0; k + 1 < MLOG; ++k) {
    for(int u = 1; u <= n; ++u) {
      if(fa[k][u] == -1) fa[k + 1][u] = -1;
      else fa[k + 1][u] = fa[k][fa[k][u]];
    }
  }
}
int ask_lca(int u, int v) {
  if(dep[u] < dep[v]) swap(u, v);
  for(int k = 0; k < MLOG; ++k) {
    if((dep[u] - dep[v]) & (1 << k)) u = fa[k][u];
  }
  if(u == v) return u;
  for(int k = MLOG - 1; k >= 0; --k) {
    if(fa[k][u] != fa[k][v])
      u = fa[k][u], v = fa[k][v];
  }
  return fa[0][u];
}
bool vis[MAXV];
int mex, cnt[MAXV];
void del(int v) {
  cnt[v]--;
  if(!cnt[v] && mex > v) {
    mex = v;
  }
}
void add(int v) {
  cnt[v]++;
  if(mex == v) {
    while(cnt[++mex]);
  }
}
void xorNode(int u) {
  if(vis[u]) {
    vis[u] = false;
    del(val[u]);
  } else {
    vis[u] = true;
    add(val[u]);
  }
}
void xorPathWithoutLca(int u, int v) {
  if(dep[u] < dep[v]) swap(u, v);
  while(dep[u] != dep[v])
    xorNode(u), u = fa[0][u];
  while(u != v)
    xorNode(u), u = fa[0][u],
    xorNode(v), v = fa[0][v];
}
void moveNode(int u, int v, int taru, int tarv) {
  xorPathWithoutLca(u, taru);
  xorPathWithoutLca(v, tarv);
  xorNode(ask_lca(u, v));
  xorNode(ask_lca(taru, tarv));
}
void make_ans() {
  for(int i = 0; i < m; ++i) ask[i].adjust();
  sort(ask, ask + m);
  int nowu = 1, nowv = 1; xorNode(1);
  for(int i = 0; i < m; ++i) {
    moveNode(nowu, nowv, ask[i].u, ask[i].v);
    ans[ask[i].id] = mex;
    nowu = ask[i].u, nowv = ask[i].v;
  }
}
void print_ans() {
  for(int i = 0; i < m; ++i)
    if(ans[i] > n) ans[i] = n;
    printf("%d\n", ans[i]);
}
int main() {
  read();
  init_block();
  init_lca();
  make_ans();
  print_ans();
  return 0;
}
