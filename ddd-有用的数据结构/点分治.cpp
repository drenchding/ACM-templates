#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

const int MAXN = 20005;

int n, root, sz, ans1, ans2;
int w[MAXN], x[MAXN], y[MAXN], vis[MAXN], dis[MAXN];
int size[MAXN], f[MAXN], cnt1[MAXN], cnt2[MAXN];

struct edge {
  int x, y;
  edge(){}
  edge(int X, int Y) : x(X), y(Y){}
};

vector<edge> G[MAXN];

void getroot(int cur, int fa) {
  size[cur] = 1;
  f[cur] = 0;
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i].x;
    if(nx == fa || vis[nx]) {
      continue;
    }
    getroot(nx, cur);
    size[cur] += size[nx];
    f[cur] = max(f[cur], size[nx]);
  } 
  f[cur] = max(f[cur], sz - f[cur]);
  if(f[cur] < f[root]) root = cur;
}

void dfs(int cur, int fa) {
  cnt2[dis[cur]]++;
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i].x;
    if(nx == fa || vis[nx]) continue;
    dis[nx] = (dis[cur] + G[cur][i].y) % 3;
    dfs(nx, cur);
  }
}

void cal(int cur) {
  cnt1[0] = 1; ans1++;
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i].x;
    dis[nx] = G[cur][i].y;
    if(vis[nx]) continue;
    dfs(nx, cur);
    for(int j = 0; j < 3; j++) {
      ans1 += cnt1[j] * cnt2[(3 - j) % 3] * 2;
    }
    for(int j = 0; j < 3; j++) {
      cnt1[j] += cnt2[j];
      cnt2[j] = 0;
    }
  }
  for(int i = 0; i < 3; i++) {
    cnt1[i] = 0;
  }
}

void solve(int cur) {
  vis[cur] = 1;
  cal(cur);
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i].x;
    if(vis[nx]) continue;
    f[0] = sz = size[nx];
    getroot(nx, root = 0);
    solve(root);
  }
}

int gcd(int a, int b) {
  if(!b) return a;
  return gcd(b, a % b);
}

int main() {
  scanf("%d", &n);
  for(int i = 1; i < n; i++) {
    scanf("%d %d %d", &x[i], &y[i], &w[i]);
    G[x[i]].push_back(edge(y[i], w[i] % 3));
    G[y[i]].push_back(edge(x[i], w[i] % 3));
  }
  f[0] = sz = n;
  getroot(1, root = 0);
  solve(root);
  ans2 = n * n;
  int d = gcd(ans1, ans2);
  ans1 /= d; ans2 /= d;
  printf("%d/%d\n", ans1, ans2);
  return 0;
}