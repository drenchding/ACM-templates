#include <bits/stdc++.h>

const int MAXN = 300005;

using namespace std;

int n, m, val[MAXN];

struct LCT {
  int top, c[MAXN][2], fa[MAXN], xr[MAXN], q[MAXN], rev[MAXN];
  void pushup(int x) { 
    xr[x] = xr[c[x][0]] ^ xr[c[x][1]] ^ val[x];
  }
  void pushdown(int x){
    int l = c[x][0], r = c[x][1];
    if(rev[x]) {
      rev[l] ^= 1; rev[r] ^= 1; rev[x] ^= 1;
      swap(c[x][0], c[x][1]);
    }
  }
  bool isroot(int x) {
    return c[fa[x]][0] != x && c[fa[x]][1] != x;
  }
  void rotate(int x) {
    int y = fa[x], z = fa[y], l, r;
    if(c[y][0] == x) l = 0; else l = 1; r = l ^ 1;
    if(!isroot(y)) {
      if(c[z][0] == y) c[z][0] = x; else c[z][1] = x;
    }
    fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
    c[y][l] = c[x][r]; c[x][r] = y;
    pushup(y); pushup(x);
  }
  void splay(int x){
    top = 1; q[top] = x;
    for(int i = x; !isroot(i); i = fa[i]) q[++top] = fa[i];
    for(int i = top; i; i--) pushdown(q[i]);
    while(!isroot(x)) {
      int y = fa[x], z = fa[y];
      if(!isroot(y)) {
        if((c[y][0] == x) ^ (c[z][0] == y)) rotate(x); else rotate(y);
      }
      rotate(x);
    }
  }
  void access(int x) {
    for(int t = 0; x; t = x, x = fa[x]) splay(x), c[x][1] = t, pushup(x);
  }
  void makeroot(int x) {
    access(x); splay(x); rev[x] ^= 1;
  }
  int find(int x) {
    access(x); splay(x); while(c[x][0]) x = c[x][0]; return x;
  }
  void split(int x, int y) {
    makeroot(x); access(y); splay(y);
  }
  void cut(int x, int y) {
    split(x, y); if(c[y][0] == x) c[y][0] = 0, fa[x] = 0;
  }
  void link(int x, int y) {
    makeroot(x); fa[x] = y;
  }
}T;
int read() {
  int x; scanf("%d", &x); return x;
}
int main() {
  n = read(); m = read();
  for(int i = 1; i <= n; i++) val[i] = read(), T.xr[i] = val[i];
  while(m--) {
    int opt = read();
    if(opt == 0){
      int x = read(), y = read(); T.split(x, y);
      printf("%d\n", T.xr[y]);
    } else if(opt == 1) {
      int x = read(), y = read(), xx = T.find(x), yy = T.find(y);
      if(xx != yy) T.link(x, y);
    } else if(opt == 2) {
      int x = read(), y = read(), xx = T.find(x), yy = T.find(y);
      if(xx == yy) T.cut(x, y);
    } else if(opt == 3) {
      int x = read(), y = read();
      T.access(x); T.splay(x); val[x] = y; T.pushup(x);
    }
  }
  return 0;
}
