#include <set>
#include <vector>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef pair<ll, int> Point;

const int MAXN = 100005;
const ll INF = 1LL << 50;
const int dx[] = {1, 1};
const int dy[] = {-1, 1};

set<Point> S[2];

int n, cnt, x[MAXN], y[MAXN];
ll a[MAXN][2], ans;

int pa[MAXN];

vector<int> G[MAXN];

inline bool merge(int x, int y) {
  x = pa[x], y = pa[y];
  if(x == y) return false;
  if(G[x].size() > G[y].size()) swap(x, y);
  for(int i = 0; i < (int)G[x].size(); i++) {
    G[y].push_back(G[x][i]);
    pa[G[x][i]] = y;
  }
  G[x].clear();
  return true; 
}

struct Edge {
  int u, v, w;
  Edge(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) { }
}E[MAXN];

int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d %d", &x[i], &y[i]);
    for(int j = 0; j < 2; j++) {
      a[i][j] = x[i] * dx[j] + y[i] * dy[j];
      S[j].insert(Point(a[i][j], i));
    }
  }
  for(int i = 1; i <= n; i++) {
    pa[i] = i;
    G[i].push_back(i);
  }
  while(1) {
    int finished = 0; cnt = 0;
    for(int i = 1; i <= n; i++) {
      if(pa[i] != i) continue;
      if(G[i].size() == n) {
        finished = 1; break;
      }
      for(int j = 0; j < (int)G[i].size(); j++) {
        for(int k = 0; k < 2; k++) {
          S[k].erase(Point(a[G[i][j]][k], G[i][j]));
        }
      }
      ll maxV = -INF; int v = -1;
      for(int k = 0; k < 2; k++) {
        ll maxU = -INF, minU = INF;
        for(int j = 0; j < (int)G[i].size(); j++) {
          maxU = max(maxU, a[G[i][j]][k]);
          minU = min(minU, a[G[i][j]][k]);
        }
        set<Point>::iterator it1 = S[k].begin();
        set<Point>::iterator it2 = S[k].end(); it2--;
        if(maxU - it1->first > -minU + it2->first) {
          if(maxU - it1->first > maxV) {
            maxV = maxU - it1->first;
            v = it1->second;
          }
        } else {
          if(-minU + it2->first > maxV) {
            maxV = -minU + it2->first;
            v = it2->second;
          }
        }
      }
      E[++cnt] = Edge(i, v, maxV);
      for(int j = 0; j < (int)G[i].size(); j++) {
        for(int k = 0; k < 2; k++) {
          S[k].insert(Point(a[G[i][j]][k], G[i][j]));
        }
      }
    }
    if(finished) break;
    for(int j = 1; j <= cnt; j++) {
      if(merge(E[j].u, E[j].v)) {
        ans += E[j].w;
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}