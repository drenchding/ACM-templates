#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 105;
int n, cnt, cntx, cnty;
double prex[MAXN<<1], prey[MAXN<<1];
double cx[MAXN<<1], cy[MAXN<<1];
struct line {
  int s, t, v;
};
vector<line> V[MAXN<<1];
struct Node {
  int cov;
  double len;
  Node *ls, *rs;
  Node(): cov(0), len(0.0) { }
  void init() {
    cov = 0;
    len = 0.0;
    ls = NULL;
    rs = NULL;
  }
  void pushup(int l, int r) {
    if(cov) {
      len = prey[r + 1] - prey[l];
    } else if(l == r) {
      len = 0;
    } else {
      len = ls->len + rs->len;
    }
  }
}pool[MAXN<<2], *root;
struct rec {
  double x1, y1, x2, y2;
  int _x1, _y1, _x2, _y2;
  void input() {
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    cx[++cntx] = x1, cx[++cntx] = x2;
    cy[++cnty] = y1; cy[++cnty] = y2;
  }
  void disp() {
    _x1 = lower_bound(cx + 1, cx + cntx + 1, x1) - cx, prex[_x1] = x1;
    _x2 = lower_bound(cx + 1, cx + cntx + 1, x2) - cx, prex[_x2] = x2;
    _y1 = lower_bound(cy + 1, cy + cnty + 1, y1) - cy, prey[_y1] = y1;
    _y2 = lower_bound(cy + 1, cy + cnty + 1, y2) - cy, prey[_y2] = y2;
  }
  void add() {
    V[_x1].push_back(line{_y1, _y2, 1});
    V[_x2].push_back(line{_y1, _y2, -1});
  }
}R[MAXN];
Node *newNode() {
  pool[cnt].init();
  return &pool[cnt++];
}
Node *build(int l, int r) {
  Node *cur = newNode();
  if(l == r) {
    return cur;
  }
  int mid = (l + r) / 2;
  cur->ls = build(l, mid);
  cur->rs = build(mid + 1, r);
  return cur;
}
void add(Node *cur, int l, int r, int a, int b, int v) {
  if(a <= l && b >= r) {
    cur->cov += v;
    cur->pushup(l, r);
    return;
  }
  int mid = (l + r) / 2;
  if(a <= mid) add(cur->ls, l, mid, a, b, v);
  if(b > mid) add(cur->rs, mid + 1, r, a, b, v);
  cur->pushup(l, r);
}
int main() {
  int testCase = 0;
  while(scanf("%d", &n) != -1) {
    if(n == 0) break;
    cnt = cntx = cnty = 0;
    for(int i = 1; i <= n; i++) {
      R[i].input();
    }
    for(int i = 1; i <= cntx; i++) {
      V[i].clear();
    }
    sort(cx + 1, cx + cntx + 1);
    sort(cy + 1, cy + cnty + 1);
    for(int i = 1; i <= n; i++) {
      R[i].disp();
      R[i].add();
    }
    root = build(1, cnty);
    double res = 0;
    for(int i = 1; i <= cntx; i++) {
      res += root->len * (prex[i] - prex[i - 1]);
      for(int j = 0; j < V[i].size(); j++) {
        if(V[i][j].s < V[i][j].t) {
          add(root, 1, cntx, V[i][j].s, V[i][j].t - 1, V[i][j].v);
        }
      }
    }
    printf("Test case #%d\nTotal explored area: %.2lf\n\n", ++testCase, res);
  }
  return 0;
}