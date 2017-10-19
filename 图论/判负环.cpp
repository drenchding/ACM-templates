#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 400005;
int n, m, ok, vis[MAXN], dis[MAXN];

struct edge {
  int to, dis;
  edge(){}
  edge(int To, int Dis) : to(To), dis(Dis){}
};

vector<edge> G[MAXN];

void spfa(int cur) {
  if(ok) return;
  vis[cur] = 1;
  for(int i = 0; i < G[cur].size(); i++) {
    if(ok) return;
    edge & nx = G[cur][i];
    if(dis[cur] + nx.dis < dis[nx.to]) {
      dis[nx.to] = dis[cur] + nx.dis;
      if(vis[nx.to]) {
        ok = 1;
        return;
      }
      spfa(nx.to);
    }
  }
  vis[cur] = 0;
}

int main() {
  int T; scanf("%d", &T);
  while(T--) {
    memset(vis, 0, sizeof(dis));
    memset(dis, 0, sizeof(dis));
    ok = 0; dis[1] = 0;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) G[i].clear();
    for(int i = 1; i <= m; i++) {
      int x, y, t;
      scanf("%d %d %d", &x, &y, &t);
      G[x].push_back(edge(y, t));
      if(t >= 0) G[y].push_back(edge(x, t));
    }
    for(int i = 1; i <= n; i++) {
      spfa(i);
      if(ok) break;
    }
    if(ok) puts("YE5");
    else puts("N0");
  }
  return 0;
}