//一开始有N个小根堆，每个堆包含且仅包含一个数。接下来需要支持两种操作：
// 1 x y 将第x个数和第y个数所在的小根堆合并
//（若第x或第y个数已经被删除或第x和第y个数在用一个堆内，则无视此操作）
// 2 x 输出第x个数所在的堆最小数，并将其删除
// （若第x个数已经被删除，则输出-1并无视删除操作）

#include <cstdio>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <algorithm>

const int MAXN = 200005;

using namespace std;

int n, m, segNode;

struct Node {
  int size, val, pos;
  Node *ls, *rs;
  Node(): ls(NULL), rs(NULL) { }
  Node(int s, int v, Node *l, Node *r): size(s), val(v), ls(l), rs(r) { }
}pool[MAXN], *st[MAXN], *root[MAXN], *null;

Node *newNode(int s, int v, Node *l, Node *r) {
  return &(*st[segNode++] = Node(s, v, l, r));
}

int read() {
  int x; scanf("%d", &x); return x;
}

void pushup(Node *cur) {
  if(cur->ls->size) {
    cur->size = cur->ls->size + cur->rs->size;
    cur->val = max(cur->ls->val, cur->rs->val);
    if(cur->ls->val > cur->rs->val) {
      cur->pos = cur->ls->pos;
    } else if(cur->ls->val < cur->rs->val) {
      cur->pos = cur->rs->pos;
    } else {
      cur->pos = min(cur->ls->pos, cur->rs->pos);
    }
  }
}

Node *merge(Node *a, Node *b) {
  if(a->size > b->size * 4) {
    a->rs = merge(a->rs, b);
    pushup(a); return a;
  }
  if(b->size > a->size * 4) {
    b->ls = merge(a, b->ls);
    pushup(b); return b;
  }
  Node *cur = newNode(a->size + b->size, max(a->val, b->val), a, b);
  pushup(cur); return cur;
}

void erase(Node *cur) {
  if(cur->ls->size) {
    if(cur->ls->val == cur->val) {
      erase(cur->ls);
    } else {
      erase(cur->rs);
    }
    pushup(cur);
  } else {
    cur->val = -INT_MAX - 1;
  }
}

int pa[MAXN], del[MAXN];
int v[MAXN], b[MAXN], c[MAXN];

int find(int cur) {
  if(pa[cur] == cur) {
    return cur;
  } else {
    pa[cur] = find(pa[cur]);
    return pa[cur];
  }
}

int main() {
  n = read(); m = read();
  for(int i = 0; i < 2 * n; i++) {
    st[i] = &pool[i];
  }
  null = newNode(0, 0, 0, 0);
  for(int i = 1; i <= n; i++) {
    b[i] = v[i] = read();
  }
  sort(b + 1, b + n + 1);
  for(int i = 1; i <= n; i++) {
    int p = lower_bound(b + 1, b + n + 1, v[i]) - b;
    c[p] = v[i], v[i] = p;
  }
  for(int i = 1; i <= n; i++) {
    int x = v[i];
    root[i] = newNode(1, -x, null, null);
    root[i]->pos = i;
    pa[i] = i;
  }
  while(m--) {
    int opt = read();
    if(opt == 1) {
      int x = read(), y = read();
      if(del[x] || del[y]) continue;
      int a = find(x), b = find(y);
      if(a == b) continue;
      pa[a] = b;
      root[b] = merge(root[a], root[b]);
    } else {
      int x = read();
      if(del[x]) {
        puts("-1");
      } else {
        int res = -root[find(x)]->val;
        del[root[find(x)]->pos] = 1;
        erase(root[find(x)]);
        printf("%d\n", c[res]);
      }
    }
  }
  return 0;
}