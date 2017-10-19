// 从前一个和谐的班级，有 nl 个是男生，有 nr 个是女生。编号分别为 1, …, nl 和 1, …, nr。
// 有若干个这样的条件：第 v 个男生和第 u 个女生愿意结为配偶，且结为配偶后幸福程度为 w。
// 请问这个班级里幸福程度之和最大是多少？

#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 505;
const int INF = (int) (1e9);

int vis[MAXN], slack[MAXN], mat[MAXN], pre[MAXN], g[MAXN][MAXN], ltag[MAXN], rtag[MAXN];

int n, m, nl, nr;

void augment(int s) {
  for(int i = 0; i <= n; i++) {
    vis[i] = 0;
    slack[i] = INF;
  }
  int v = 0, u;
  mat[v] = s;
  do {
    int a = INF, mn = 0;
    vis[v] = 1, u = mat[v];
    for(int i = 1; i <= n; i++) {
      if(!vis[i]) {
        if(ltag[u] + rtag[i] - g[u][i] < slack[i]) {
          slack[i] = ltag[u] + rtag[i] - g[u][i];
          pre[i] = v;
        }
        if(slack[i] < a) {
          a = slack[i];
          mn = i;
        }
      }
    }
    for(int i = 0; i <= n; i++) {
      if(vis[i]) {
        ltag[mat[i]] -= a;
        rtag[i] += a; 
      } else {
        slack[i] -= a;
      }
    }
    v = mn;
  } while(mat[v]);
  while(v) {
    u = pre[v];
    mat[v] = mat[u];
    v = u;
  }
}

int main() {
  cin >> nl >> nr >> m;
  n = max(nl, nr);
  for(int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> v >> u >> w;
    g[u][v] = w;
  }
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      ltag[i] = max(ltag[i], g[i][j]);
    }
  } 
  for(int i = 1; i <= n; i++) {
    augment(i);
  }
  long long ans = 0;
  for(int i = 1; i <= n; i++) {
    ans += ltag[i] + rtag[i];
  }
  cout << ans << endl;
  for(int i = 1; i <= nl; i++) {
    cout << (g[mat[i]][i] ? mat[i] : 0) << endl;
  }
  return 0;
}