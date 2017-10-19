#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 50005;

int n, m, S, c[MAXN], ans[MAXN];

struct ask {
  int l, r, id, b;
  ask() {}
  ask(int A, int B, int C) : l(A), r(B), id(C), b(l / S){}
  bool operator<(const ask other) const {
    if(b == other.b) return r < other.r;
    return b < other.b;
  }
}Q[MAXN];

void ins(int pos) {

}

void del(int pos) {

}

int getAns() {
  
}

int main() {
  scanf("%d %d", &n, &m);
  S = (int)sqrt(n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &c[i]);
  }
  for(int i = 1; i <= m; i++) {
    int l, r; scanf("%d %d", &l, &r);
    Q[i] = ask(l, r, i);
  }
  sort(Q + 1, Q + m + 1);
  int l = 1, r = 0; 
  for(int i = 1; i <= m; i++) {
    while(r < Q[i].r) ins(++r);
    while(l > Q[i].l) ins(--l);
    while(r > Q[i].r) del(r--);
    while(l < Q[i].l) del(l++);
    ans[Q[i].id] = getAns();
  }
  for(int i = 1; i <= m; i++) {
  printf("%d\n", ans[i]);
  } 
  return 0;
}
