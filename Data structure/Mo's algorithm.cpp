// 统计区间内 a[i] * cnt[a[i]] 的最值
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100005;
int B, n, q, cnt[MAXN];
int a[MAXN], b[MAXN], c[MAXN];
struct Ask {
  int l, r, id, b;
  Ask() { }
  Ask(int L, int R, int Id): l(L), r(R), id(Id), b((L - 1) / B + 1) { }
  bool operator<(const Ask & rhs) const {
    return b == rhs.b ? r < rhs.r : b < rhs.b;
  }
}Q[MAXN];
inline int getBlock(int p) { 
  return (p - 1) / B + 1; 
}
inline int getStart(int b) { 
  return (b - 1) * B + 1; 
}
inline int getEnd(int b) { 
  return min(getStart(b + 1) - 1, n); 
}
ll curAns, ans[MAXN];
int curL, curR; // 左边到了哪，右边到了哪
void addR() {
  int v = a[curR];
  cnt[v]++;
  curAns = max(curAns, 1LL * cnt[v] * c[v]);
}
void addL() {
  int v = a[curL];
  cnt[v]++;
  curAns = max(curAns, 1LL * cnt[v] * c[v]);
}
void undoL() {
  int v = a[curL];
  cnt[v]--;
}
ll brute(int l, int r) {
  ll res = 0;
  for(int k = l; k <= r; k++) {
    cnt[a[k]]++;
    res = max(res, 1LL * cnt[a[k]] * c[a[k]]);
  }
  for(int k = l; k <= r; k++) cnt[a[k]]--;
  return res;
}
int main() {
  scanf("%d %d", &n, &q);
  B = (int)sqrt(1.0 * n * n / q);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    b[i] = a[i];
  }
  sort(b + 1, b + n + 1);
  int tot = unique(b + 1, b + n + 1) - b - 1;
  for(int i = 1; i <= n; i++) {
    int p = lower_bound(b + 1, b + tot + 1, a[i]) - b;
    c[p] = a[i], a[i] = p;
  }
  for(int i = 1; i <= q; i++) {
    int l, r;
    scanf("%d %d", &l, &r);
    Q[i] = Ask(l, r, i);
  }
  sort(Q + 1, Q + q + 1);
  for(int i = 1, p; i <= q; i = p) {
    for(int j = i + 1; j <= q + 1; j++) {
      if(Q[j].b != Q[i].b) {
        p = j; break;
      }
    }
    memset(cnt, 0, sizeof(cnt));
    curAns = 0;
    int curB = Q[i].b;
    curR = getEnd(curB);
    for(int j = i; j <= p - 1; j++) {
      int l = Q[j].l, r = Q[j].r;
      if(getBlock(l) == getBlock(r)) {
        ans[Q[j].id] = brute(l, r);
      } else {
        while(curR < r) ++curR, addR(); // 右指针向右走
        long long preAns = curAns; // 保存下只考虑右边的答案
        curL = getEnd(curB) + 1;
        while(curL > l) --curL, addL(); // 左指针向左走
        ans[Q[j].id] = curAns;
        while(curL < getEnd(curB) + 1) undoL(), ++curL;
        curAns = preAns;
      }
    }
  }
  for(int i = 1; i <= q; i++) {
    printf("%lld\n", ans[i]);
  }
  return 0;
}