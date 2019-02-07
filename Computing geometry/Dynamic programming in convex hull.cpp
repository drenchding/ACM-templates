// 给出 n 个点和一个 l，问用长度为 l 的绳子至多能围多少点
// 保证没有三点共线

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 85;
const double INF = 1e12;
const double eps = 1e-9;

struct Point {
  double x, y;
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
int inLine[MAXN][MAXN];
int n;
double l, dp[MAXN][MAXN], dist[MAXN][MAXN];

int sgn(double x) {
  if(fabs(x) <= eps) return 0;
  if(x > eps) return 1;
  if(x < -eps) return -1;
}

int cross(const Point & a, const Point & b) {
  return sgn(a.x * b.y - a.y * b.x);
}

bool inSeg(int a, int b, int c) {
  if(cross(P[b] - P[a], P[c] - P[a]) != 0) return false;
  return (P[a].x - P[c].x) * (P[b].x - P[c].x) <= 0
      && (P[a].y - P[c].y) * (P[b].y - P[c].y) <= 0;
}

int have(int a, int b, int c) {
  return (d[a][b] & d[b][c] & d[c][a]).count();
}

int have(int a, int b) {
  if(a > b) swap(a, b);
  return inLine[a][b];
}

double dis(int a, int b) {
  return sqrt((double)((P[a].x - P[b].x) * (P[a].x - P[b].x)) + 
              (double)((P[a].y - P[b].y) * (P[a].y - P[b].y)));
}

int main() {
  int T;
  scanf("%d", &T);
  int Case = 0;
  while(T--) {
    scanf("%d %lf", &n, &l);
    for(int i = 1; i <= n; i++) {
      scanf("%lf %lf", &P[i].x, &P[i].y);
    }
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++) {
        dist[i][j] = dis(i, j);
      }
    }
    int tot = 0;
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++) {
        if(i == j) continue;
        L[++tot] = Line{i, j, atan2(P[j].y - P[i].y, P[j].x - P[i].x)};
      }
    }
    sort(L + 1, L + tot + 1);
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++) {
        if(i == j) continue;
        d[i][j].reset();
        for(int k = 1; k <= n; k++) {
          if(cross(P[j] - P[i], P[k] - P[i]) > 0) {
            d[i][j].set(k);
          }
        }
      }
    }
    for(int i = 1; i <= n; i++) {
      for(int j = i; j <= n; j++) {
        inLine[i][j] = 0;
        for(int k = 1; k <= n; k++) {
          inLine[i][j] += inSeg(i, j, k);
        }
      }
    }
    int ans = 1;
    for(int s = 1; s <= n; s++) {
      for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
          dp[i][j] = INF;
        }
      }
      dp[s][1] = 0;
      for(int i = 1; i <= tot; i++) {
        int from = L[i].a, to = L[i].b;
        if(cross(P[to] - P[from], P[s] - P[from]) < 0) continue;
        int cnt = have(s, from, to) + have(from, to) + have(s, to) - 3;
        if(from == s) {
          cnt = have(from, to) - 1;
        } else if(to == s) {
          cnt = 0;
        }
        for(int j = cnt + 1; j <= n; j++) {
          dp[to][j] = min(dp[to][j], dp[from][j - cnt] + dist[from][to]);
        }
      }
      for(int j = 1; j <= n; j++) if(dp[s][j] <= l) ans = max(ans, j);
    }
    printf("Case #%d: %d\n", ++Case, ans);
  }
  return 0;
}