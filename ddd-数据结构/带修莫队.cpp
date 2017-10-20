#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;

int S, n, m, cnt1, cnt2, now;
int a[MAXN], b[MAXN], cnt[MAXN], ans[MAXN], vis[MAXN];

struct ask {
  int l, r, t, id, lb, rb;
  ask(){}
  ask(int L, int R, int T, int ID) {
    l = L; r = R; t = T; id = ID;
    lb = l / S; rb = r / S;
  }
  bool operator<(const ask & a) const {
    if(lb == a.lb) {
      if(rb == a.rb) return t < a.t;
      return rb < a.rb;
    }
    return lb < a.lb;
  }
}Q[MAXN];

struct modify {
  int pos, color, pre;
  modify(){}
  modify(int P, int C, int PR): pos(P), color(C), pre(PR){}
}M[MAXN];

void inst(int t) {
  if(vis[M[t].pos]) {
    cnt[a[M[t].pos]]--;
    if(!cnt[a[M[t].pos]]) now--;
  }
  a[M[t].pos] = M[t].color;
  if(vis[M[t].pos]) {
    if(!cnt[a[M[t].pos]]) now++;
    cnt[a[M[t].pos]]++;
  }
}

void delt(int t) {
  if(vis[M[t].pos]) {
    cnt[a[M[t].pos]]--;
    if(!cnt[a[M[t].pos]]) now--;
  }
  a[M[t].pos] = M[t].pre;
  if(vis[M[t].pos]) {
    if(!cnt[a[M[t].pos]]) now++;
    cnt[a[M[t].pos]]++;
  }
}

void ins(int pos) {
  vis[pos] = 1;
  if(!cnt[a[pos]]) now++;
  cnt[a[pos]]++;
}

void del(int pos) {
  vis[pos] = 0;
  cnt[a[pos]]--;
  if(!cnt[a[pos]]) now--;
}

int main() {
  scanf("%d %d", &n, &m);
  S = (int)pow(n, 2.0 / 3.0);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    b[i] = a[i];
  }
  for(int i = 1; i <= m; i++) {
    char s[2]; scanf("%s", s);
    int x, y; scanf("%d %d", &x, &y);
    if(s[0] == 'Q') Q[++cnt1] = ask(x, y, cnt2, cnt1);
    else {
      M[++cnt2] = modify(x, y, b[x]);
      b[x] = y;
    }
  }
  sort(Q + 1, Q + cnt1 + 1);
  int l = 1, r = 0, t = 0;
  now = 0;
  for(int i = 1; i <= cnt1; i++) {
    while(t < Q[i].t) inst(++t);
    while(t > Q[i].t) delt(t--);
    while(r < Q[i].r) ins(++r);
    while(l > Q[i].l) ins(--l);
    while(r > Q[i].r) del(r--);
    while(l < Q[i].l) del(l++);
    ans[Q[i].id] = now;
  }
  for(int i = 1; i <= cnt1; i++)
    printf("%d\n", ans[i]);
  return 0;
}
