// 本题中你需要求解一个标准型线性规划：
// 有 n 个实数变量 x1, x2, …, xn 和 m 条约束，其中第 i 条约束形如 \sum_{j = 1}^{n} a_{ij} x_{j} \leq b_{i}
// 此外这 n 个变量需要满足非负性限制，即 x_{j} \geq 0。
// 在满足上述所有条件的情况下，你需要指定每个变量 x_{j} 的取值
// 使得目标函数 F = \sum_{j = 1}^{n} c_{j} x_{j} 的值最大。

#include <bits/stdc++.h>

using namespace std;

typedef long double db;

const db eps = 1e-8;

const int N = 25;

int n, m, id_B[N], id_N[N];
db a[N][N];

void pivot(int l, int e) {
  swap(id_B[l], id_N[e]);
  db tmp = -a[l][e];
  a[l][e] = -1;
  static int arr[N];
  int tot = 0;
  for(int i = 0; i <= n; i++) {
    if(fabs(a[l][i]) > eps) {
      arr[tot++] = i;
      a[l][i] /= tmp;
    }
  }
  for(int i = 0; i <= m; i++) {
    if(i != l && fabs(a[i][e]) > eps) {
      tmp = a[i][e];
      a[i][e] = 0;
      for(int j = 0; j < tot; j++) {
        a[i][arr[j]] += tmp * a[l][arr[j]];
      }
    }
  }
}

bool simplex() {
  while(1) {
    int l = 0, e = 0;
    for(int i = 1; i <= n; i++) {
      if(a[0][i] > eps && (!e || id_N[i] < id_N[e])) e = i;
    }
    if(!e) return true;
    bool flag = false;
    db mi = 1e20;
    for(int i = 1; i <= m; i++) {
      if(a[i][e] < -eps) {
        if(!flag) flag = true, mi = -a[i][0] / a[i][e];
        else mi = min(mi, -a[i][0] / a[i][e]);
      }
    }
    for(int i = 1; i <= m; i++) {
      if(a[i][e] < -eps && fabs(-a[i][0] / a[i][e] - mi) < eps && (!l || id_B[i] < id_B[l])) l = i;
    }
    if(!l) return false;
    pivot(l, e);
  }
}

bool init_simplex() {
  int l;
  db mi = 0;
  for(int i = 1; i <= m; i++) {
    if(a[i][0] < mi) mi = a[l = i][0];
    for(int j = 1; j <= n; j++) a[i][j] *= -1;
  }
  if(mi > -eps) return true;
  static db arr[N];
  for(int i = 1; i <= n; i++) {
    arr[i] = a[0][i];
    a[0][i] = 0;
  }
  a[0][++n] = -1;
  for(int i = 1; i <= m; i++) a[i][n] = 1;
  pivot(l, n);
  simplex();
  if(a[0][0] < -eps) return false;
  for(int i = 1; i <= m; i++) if(!id_B[i]) {
    for(int j = 1; j <= n; j++) if(fabs(a[i][j]) > eps) {
      pivot(i, j);
      break;
    }
    break;
  }
  int e;
  for(int i = 1; i <= n; i++) if(!id_N[i]) {
    e = i;
    break;
  }
  if(e != n) {
    id_N[e] = id_N[n];
    for(int i = 1; i <= m; i++) a[i][e] = a[i][n];
  }
  --n;
  for(int i = 1; i <= n; i++) a[0][i] = 0;
  for(int i = 1; i <= m; i++) if(id_B[i] <= n) {
    for(int j = 0; j <= n; j++) {
      a[0][j] += a[i][j] * arr[id_B[i]];
    }
  }
  for(int i = 1; i <= n; i++) if(id_N[i] <= n)
    a[0][i] += arr[id_N[i]];
  return true;
}

int main() {
  bool type;
  cin >> n >> m >> type;
  for(int i = 1; i <= n; i++) {
    scanf("%Lf", &a[0][i]);
    id_N[i] = i;
  }
  for(int i = 1; i <= m; i++) {
    for(int j = 1; j <= n; j++) {
      scanf("%Lf", &a[i][j]);
    }
    scanf("%Lf", &a[i][0]);
    id_B[i] = n + i;
  }
  if(!init_simplex()) return puts("Infeasible"), 0;
  if(!simplex()) return puts("Unbounded"), 0;
  printf("%.10Lf\n", a[0][0]);
  if(type) {
    static db ans[N];
    for(int i = 1; i <= m; i++) {
      if(id_B[i] <= n) {
        ans[id_B[i]] = a[i][0];
      }
    }
    for(int i = 1; i <= n; i++) {
      printf("%.10Lf%c", ans[i], " \n"[i == n]);
    }
  }
  return 0;
}