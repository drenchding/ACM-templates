#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;
const int INF = (int)1e9;

struct Point {
  int x, y;
  Point operator-(const Point & rhs) const {
    return Point{x - rhs.x, y - rhs.y};
  }
}P[MAXN];

struct Line {
  int a, b;
  double ang;
  bool operator<(const Line & rhs) const {
    return ang < rhs.ang;
  }
}L[MAXN*MAXN];

bitset<MAXN> d[MAXN][MAXN];
bool inLine[MAXN][MAXN];
int n, f[MAXN], g[MAXN];
// f[i]: 以 i 为最后一个点的，且 s->i 没有其它点的最大空凸包面积
// g[i]: 以 i 为最后一个点的最大空凸包面积
int id[MAXN][MAXN], ind[MAXN*MAXN];
vector<int> G[MAXN*MAXN];

int cross(const Point & a, const Point & b) {
  return a.x * b.y - a.y * b.x;
}

void addEdge(int x, int y) {
  G[x].push_back(y);
  ++ind[y];
}

bool inSeg(int a, int b, int c) { // c 是否在 a->b 上
  if(cross(P[b] - P[a], P[c] - P[a]) != 0) return false;
  return (P[a].x - P[c].x) * (P[b].x - P[c].x) <= 0
      && (P[a].y - P[c].y) * (P[b].y - P[c].y) <= 0;
}

bool have(int a, int b, int c) { // a->b->c->a 内部有无其它点
  return (d[a][b] & d[b][c] & d[c][a]).any();
}

bool have(int a, int b) { // a->b 上有无其它点
  if(a > b) swap(a, b);
  return inLine[a][b];
}

int area(int a, int b, int c) { // a->b->c->a 的面积
  return abs(cross(P[b] - P[a], P[c] - P[a]));
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    int _n; n = 0;
    scanf("%d", &_n);
    set<pair<int, int> > vis;
    for(int i = 1; i <= _n; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      if(!vis.count(make_pair(x, y))) {
        P[++n] = Point{x, y};
        vis.insert(make_pair(x, y));
      }
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++) {
        if(i == j) continue;
        id[i][j] = ++cnt;
        ind[cnt] = 0;
        G[cnt].clear();
        L[cnt] = Line{i, j, atan2(P[j].y - P[i].y, P[j].x - P[i].x)};
      }
    }
    // 如果需要保证枚举所有凸包，需要拓扑排序
    for(int i = 1; i <= cnt; i++) {
      int a = L[i].a, b = L[i].b;
      for(int c = 1; c <= n; c++) {
        if(b == c) continue;
        // a->b 和 b->c 比大小
        int j = id[b][c];
        if(L[i].ang > L[j].ang) {
          addEdge(j, i);
        } else {
          addEdge(i, j);
        }
      }
    }
    queue<int> Q;
    for(int i = 1; i <= cnt; i++) {
      if(!ind[i]) Q.push(i);
    }
    vector<Line> ord;
    while(!Q.empty()) {
      int cur = Q.front(); Q.pop();
      ord.push_back(L[cur]);
      for(int i = 0; i < G[cur].size(); i++) {
        int nx = G[cur][i];
        --ind[nx];
        if(!ind[nx]) Q.push(nx);
      }
    }
    assert(ord.size() == cnt);
    for(int i = 1; i <= cnt; i++) {
      L[i] = ord[i - 1];
    }
    // 否则直接 sort 即可
    // sort(L + 1, L + cnt + 1);
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++) {
        if(i == j) continue;
        d[i][j].reset();
        for(int k = 1; k <= n; k++) {
          if(cross(P[j] - P[i], P[k] - P[i]) > 0) {
            d[i][j].set(k); // k 在 i->j 的左边
          }
        }
      }
    }
    for(int i = 1; i <= n; i++) {
      for(int j = i; j <= n; j++) {
        inLine[i][j] = 0;
        for(int k = 1; k <= n; k++) {
          if(i == k || j == k) continue;
          inLine[i][j] |= inSeg(i, j, k);
        }
      }
    }
    int maxS = 0;
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++) {
        f[j] = g[j] = -INF;
      }
      f[i] = g[i] = 0;
      for(int j = 1; j <= cnt; j++) {
        int from = L[j].a, to = L[j].b;
        if(have(from, to)) continue; // 只枚举点数极大的凸包
        int dir = cross(P[to] - P[from], P[i] - P[from]);
        if(dir == 0) { // 出发或结束阶段，不需要管最后一条边的限制
          f[to] = max(f[to], g[from]);
          g[to] = max(g[to], g[from]);
        } else if(dir > 0) { // 中途阶段
          if(f[from] >= 0 && !have(i, from, to)) {
            int newArea = f[from] + area(i, from, to);
            g[to] = max(g[to], newArea);
            if(!have(i, to)) f[to] = max(f[to], newArea);
          }
        }
      }
      maxS = max(maxS, f[i]);
    }
    printf("%d.%d\n", maxS / 2, maxS % 2 * 5);
  }
  return 0;
}