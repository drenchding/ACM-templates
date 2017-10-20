// 树链kth，强制在线

#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
struct Node {
  int sum;
  Node *ls, *rs;
  void init() {
    sum = 0;
    ls = rs = NULL;
  }
}pool[MAXN<<6], *root[MAXN];
int n, m, tot, cnt, segNode;
int a[MAXN], b[MAXN], c[MAXN];
int size[MAXN], deep[MAXN], fa[MAXN];
int top[MAXN], dfn[MAXN], son[MAXN];
vector<int> G[MAXN];
Node *newNode() {
  pool[segNode].init();
  return &pool[segNode++];
}
Node *build(int l, int r) {
  Node *cur = newNode();
  if(l == r) return cur;
  int mid = (l + r) / 2;
  cur->ls = build(l, mid);
  cur->rs = build(mid + 1, r);
  return cur;
}
void add(Node *pre, Node *&cur, int l, int r, int p, int v) {
  cur = newNode(); *cur = *pre;
  cur->sum += v;
  if(l == r) return;
  int mid = (l + r) / 2;
  if(p <= mid) add(pre->ls, cur->ls, l, mid, p, v);
  else add(pre->rs, cur->rs, mid + 1, r, p, v);
}
int query(Node *faLca, Node *Lca, Node *x, Node *y, int l, int r, int k) {
  if(l == r) return l;
  int mid = (l + r) / 2;
  int left = x->ls->sum + y->ls->sum - Lca->ls->sum - faLca->ls->sum;
  if(left >= k) {
    return query(faLca->ls, Lca->ls, x->ls, y->ls, l, mid, k);
  } else {
    return query(faLca->rs, Lca->rs, x->rs, y->rs, mid + 1, r, k - left);
  }
}
void dfs(int cur, int fa) {
  add(root[fa], root[cur], 1, tot, a[cur], 1);
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i];
    if(nx != fa) {
      dfs(nx, cur);
    }
  }
}
void dfs1(int cur, int father, int dep) {
  fa[cur] = father;
  deep[cur] = dep;
  size[cur] = 1;
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
  dfn[cur] = ++cnt;
  if(son[cur]) dfs2(son[cur], tp);
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i];
    if(nx != fa[cur] && nx != son[cur]) {
      dfs2(nx, nx);
    }
  }
}
void dfs3(Node *cur, int l, int r) {
  if(l == r) {
    printf("%d: %d\n", l, cur->sum);
    return;
  }
  int mid = (l + r) / 2;
  dfs3(cur->ls, l, mid);
  dfs3(cur->rs, mid + 1, r);
}
void debug(Node *root) {
  dfs3(root, 1, tot);
  putchar('\n');
}
int lca(int u, int v) {
  int t1 = top[u], t2 = top[v];
  while(t1 != t2) {
    if(deep[t1] < deep[t2]) {
      swap(t1, t2); swap(u, v);
    }
    u = fa[t1], t1 = top[u];
  }
  return deep[u] < deep[v] ? u : v;
}
int main() {
  scanf("%d %d", &n, &m);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    b[i] = a[i];
  }
  sort(b + 1, b + n + 1);
  tot = unique(b + 1, b + n + 1) - b - 1;
  for(int i = 1; i <= n; i++) {
    int p = lower_bound(b + 1, b + tot + 1, a[i]) - b;
    c[p] = a[i], a[i] = p;
  }
  for(int i = 1; i < n; i++) {
    int x, y; scanf("%d %d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  root[0] = build(1, tot);
  dfs(1, 0); dfs1(1, 0, 1); dfs2(1, 1);
  int lastAns = 0;
  while(m--) {
    int u, v, k; 
    scanf("%d %d %d", &u, &v, &k);
    u ^= lastAns;
    int z = lca(u, v);
    printf("%d%s", lastAns = c[query(root[fa[z]], root[z], root[u], root[v], 1, tot, k)], m ? "\n" : "");
  }
  return 0;
}