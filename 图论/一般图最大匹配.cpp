// 从前一个和谐的班级，所有人都是搞OI的。有 n 个是男生，有 0 个是女生。男生编号分别为 1, …, n。
// 现在老师想把他们分成若干个两人小组写动态仙人掌，一个人负责搬砖另一个人负责吐槽。每个人至多属于一个小组。
// 有若干个这样的条件：第 v 个男生和第 u 个男生愿意组成小组。
// 请问这个班级里最多产生多少个小组？

#include <bits/stdc++.h>

using namespace std;

int read() {
  int x; scanf("%d", &x); return x;
}

const int MAXN = 510, MAXM = 124760;

struct edge { 
  int dt, nx; 
} e[MAXM<<1];
int h[MAXN], tot, n, m, cp[MAXN], pre[MAXN], tim, tg[MAXN], co[MAXN], f[MAXN], q[MAXN], *qh, *qt;

void addEdge(int a, int b) {
  e[++tot].dt = b, e[tot].nx = h[a], h[a] = tot;
  e[++tot].dt = a, e[tot].nx = h[b], h[b] = tot;
}

int find(int p) { 
  return p == f[p] ? p : (f[p] = find(f[p])); 
}

int lca(int a, int b) {
  tim++;
  while(1) {
    if(a) {
      if(tg[a] == tim) return a;
      tg[a] = tim; a = find(pre[cp[a]]);
    }
    swap(a, b);
  }
}

void blossom(int fx, int x, int b) {
  while(find(fx) != b) {
    pre[fx] = x, x = cp[fx];
    if(co[x] == 1) co[x] = 0, *(qt++) = x;
    if(f[x] == x) f[x] = b;
    if(f[fx] == fx) f[fx] = b;
    fx = pre[x];
  }
}

int aug(int sp) {
  for(int i = 1; i <= n; i++) co[i] = -1, pre[i] = 0, f[i] = i;
  qh = qt = q; (*qt++) = sp; co[sp] = 0;
  while(qh != qt) {
    int hn = *(qh++), nx;
    for(int pt = h[hn]; pt; pt = e[pt].nx) {      
      if(co[nx = e[pt].dt] == -1) {
        co[nx] = 1, pre[nx] = hn;
        if(!cp[nx]) {
          int fx = cp[hn], x = hn, t = nx;
          while(x) {
            cp[t] = x, cp[x] = t;
            t = fx, x = pre[fx], fx = cp[x];
          }
          return 1;
        }
        *(qt++) = cp[nx], co[cp[nx]] = 0;
      } else if(co[nx] == 0 && f[nx] != f[hn]) {
        int l = lca(hn, nx);
        blossom(hn, nx, l);
        blossom(nx, hn, l);
      }
    }
  }
  return 0;
}

int main() {
  n = read(), m = read();
  for(int i = 1; i <= m; i++) addEdge(read(), read());
  int s = 0;
  for(int i = 1; i <= n; i++) if(!cp[i]) if(aug(i)) s++;
  printf("%d\n", s);
  for(int i = 1; i <= n; i++) printf("%d ", cp[i]);
  return 0;
}