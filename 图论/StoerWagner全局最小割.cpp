#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 505;
const int INF = ~0u>>2;
int x, y, z, s, n, m, v[MAXN], mat[MAXN][MAXN], dis[MAXN];
bool vis[MAXN];
int Stoer_Wagner(int n) {
  int res = INF;
  for(int i = 0; i < n; i++) v[i] = i + 1;
  while(n > 1) {
    int maxp = 1, prev = 0;
    for(int i = 1; i < n; i++) {
      dis[v[i]] = mat[v[0]][v[i]];
      if(dis[v[i]] > dis[v[maxp]]) {
        maxp = i;
      }
    }
    memset(vis, 0, sizeof(vis));
    vis[v[0]] = true;
    for(int i = 1; i < n; i++) {
      if(i == n - 1) {
        res = min(res, dis[v[maxp]]);
        for(int j = 0; j < n; j++) {
          mat[v[prev]][v[j]] += mat[v[j]][v[maxp]];
          mat[v[j]][v[prev]] = mat[v[prev]][v[j]];
        }
        v[maxp] = v[--n];
      }
      vis[v[maxp]] = true;
      prev = maxp;
      maxp = -1;
      for(int j = 1; j < n; j++) {
        if(!vis[v[j]]) {
          dis[v[j]] += mat[v[prev]][v[j]];
          if(maxp == -1 || dis[v[maxp]] < dis[v[j]]) {
            maxp = j;
          }
        }
      }
    }
  }
  return res;
}
int main() {
  scanf("%d %d", &n, &m);
  memset(mat, 0, sizeof(mat));
  while(m--) {
    scanf("%d %d %d", &x, &y, &z);
    mat[x][y] += z;
    mat[y][x] += z;
  }
  printf("%d\n", Stoer_Wagner(n));
  return 0;
}