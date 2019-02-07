// 给出一个由小写字母组成的字符串，每次询问区间 border 长度
#include <bits/stdc++.h>

const int S = 20, N = 200000 + 10;

int n;
char s[N];

struct Info {
  int first, second, last;
  Info() {}
  Info(int x, int y, int z): first(x), second(y), last(z) {}
  void update(int t) {
    last = t;
    if (!first) first = t;
    if (!second || second == first) second = t;
  }
  bool check(int t) {
    if (second == first) return t == first;
    int d = second - first;
    if ((t - first) % d) return false;
    return first <= t && t <= last;
  }
  inline Info& operator+= (int rhs) {
    first += rhs;
    second += rhs;
    last += rhs;
    return *this;
  }
  inline Info& operator-= (int rhs) {
    first -= rhs;
    second -= rhs;
    last -= rhs;
    return *this;
  }
};

class DBF {
  int sa[S][N], rank[S][N], st[S][N], ed[S][N], k;
  bool comp(int a, int b) {
    if (rank[k - 1][a] != rank[k - 1][b]) return rank[k - 1][a] < rank[k - 1][b];
    a += (1 << (k - 1)), b += (1 << (k - 1));
    return a <= n && b <= n ? (rank[k - 1][a] < rank[k - 1][b]) : (a > b);
  }
 public:
  void build() {
    static int sum[N];
    memset(sum, 0, sizeof sum);
    for (int i = 1; i <= n; ++i) ++sum[rank[0][i] = s[i]];
    for (int i = 1; i < 256; ++i) sum[i] += sum[i - 1];
    for (int i = n; i > 0; --i) sa[0][sum[rank[0][i]]--] = i;
    for (int i = 1; i <= n; ++i) rank[0][sa[0][i]] = rank[0][sa[0][i - 1]] + (s[sa[0][i - 1]] != s[sa[0][i]]);
    for (k = 1; k < S; ++k) {
      int gap = 1 << (k - 1);
      static int temp[N];
      for (int i = 1; i <= n && i <= gap; ++i) temp[i] = n - i + 1;
      for (int i = 1, tot = std::min(gap, n); i <= n; ++i) if (sa[k - 1][i] - gap > 0) temp[++tot] = sa[k - 1][i] - gap;
      memset(sum, 0, sizeof sum);
      for (int i = 1; i <= n; ++i) ++sum[rank[k - 1][i]];
      for (int i = 1; i <= n; ++i) sum[i] += sum[i - 1];
      for (int i = n; i > 0; --i) sa[k][sum[rank[k - 1][temp[i]]]--] = temp[i];
      for (int i = 1; i <= n; ++i) rank[k][sa[k][i]] = rank[k][sa[k][i - 1]] + comp(sa[k][i - 1], sa[k][i]);
    }
    for (int i = 0; i < S; ++i) {
      for (int j = 1; j <= n; ++j) {
        int t = sa[i][j];
        if (!st[i][rank[i][t]]) st[i][rank[i][t]] = j;
      }
      for (int j = n; j > 0; --j) {
        int t = sa[i][j];
        if (!ed[i][rank[i][t]]) ed[i][rank[i][t]] = j;
      }
    }
  }
  Info ipm(int p, int q, int l, int r) {
    Info res(0, 0, 0);
    int u = st[p][rank[p][q]], v = ed[p][rank[p][q]];
    int t = std::lower_bound(sa[p] + u, sa[p] + v + 1, l) - sa[p];
    if (u <= t && t <= v && sa[p][t] <= r) res.update(sa[p][t]);
    if (u <= t + 1 && t + 1 <= v && sa[p][t + 1] <= r) res.update(sa[p][t + 1]);
    t = std::upper_bound(sa[p] + u, sa[p] + v + 1, r) - sa[p] - 1;
    if (u <= t && t <= v && sa[p][t] >= l) res.update(sa[p][t]);
    return res;
  }
} dbf;

Info reverse(const Info &info, int t) {
  int d = info.second - info.first;
  Info res;
  res.first = t - info.last + 1;
  res.last = t - info.first + 1;
  res.second = std::min(res.first + d, res.last);
  return res;
}

int merge(Info a, Info b) {
  if (b.second == b.last) std::swap(a, b);
  if (a.second == a.last) {
    if (b.check(a.second)) return a.second;
    return b.check(a.first) ? a.first : 0;
  } else {
    assert(a.second - a.first == b.second - b.first);
    return std::max(a.first, b.first) <= std::min(a.last, b.last) ? std::min(a.last, b.last) : 0;
  }
}

int query(int l, int r) {
  int k = 32 - __builtin_clz(r - l + 1);
  for (int i = k; i > 0; --i) {
    int t = 1 << (i - 1);
    Info p = dbf.ipm(i - 1, l, std::max(l + 1, r - 2 * t + 2), r - t + 1), q = dbf.ipm(i - 1, r - t + 1, l, std::min(r - t, l + t - 1));
    if (!p.first || !q.first) continue;
    p += t - 1;
    p = reverse(p, r);
    q -= l - 1;
    int res = merge(p, q);
    if (res) return res + t - 1;
  }
  return 0;
}

int main() {
  int q;
  scanf("%d%d %s", &n, &q, s + 1);
  dbf.build();
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    printf("%d\n", query(l, r));
  }
  return 0;
}