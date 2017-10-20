// 维护一个序列
// 1 x val 在第 x 个数后插入一个 val
// 2 x 删除第 x 个数
// 3 x y 翻转 [x, y]
// 4 x y k [x, y] 向右移动 k 次
// 5 x y val [x, y] 加 k
// 6 x y val [x, y] 修改为 k
// 7 x y 询问 [x, y] 的和
// 8 x y 询问 [x, y] 内的 max - min
// 9 x y val 询问与 val 差的绝对值的最小值
// 10 x y k 询问 [x, y] 第 k 小的数
// 11 x y val 询问[x, y] 比 val 小的数的个数
 
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
const int ratio = 4;
const int MAXN = 200005;

int n, m, cur, tot, cnt, cnt2, null, root, a[MAXN];
int size[MAXN], ls[MAXN], rs[MAXN], val[MAXN], trash[MAXN], v[MAXN];

int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
  while(ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
  return x * f;
}

bool cmp(int a, int b) {
  return val[a] < val[b];
}

int newnode(int sz, int v, int l, int r) {
  int cur;
  if(tot) cur = trash[tot--];
  else cur = ++cnt;
  size[cur] = sz, val[cur] = v;
  ls[cur] = l, rs[cur] = r;
  return cur;
}

void update(int cur) {
  if(size[ls[cur]])
    size[cur] = size[ls[cur]] + size[rs[cur]];
}

int merge(int a, int b) {
  if(size[ls[a]] && size[ls[b]]) {
    if(size[a] > size[b] * ratio) {
      rs[a] = merge(rs[a], b);
      update(a); return a;
    }
    if(size[b] > size[a] * ratio) {
      ls[b] = merge(a, ls[b]);
      update(b); return b;
    }
  }
  return newnode(size[a] + size[b], 0, a, b);
}

void split(int cur, int x) {
  if(!size[ls[cur]] && size[cur] != 1) {
    ls[cur] = newnode(x, val[cur], null, null);
    rs[cur] = newnode(size[cur] - x, val[cur], null, null);
  }
  if(x > size[ls[cur]]) {
    split(rs[cur], x - size[ls[cur]]);
    ls[cur] = merge(ls[cur], ls[rs[cur]]);
    trash[++tot] = rs[cur];
    rs[cur] = rs[rs[cur]];
  } else if(x < size[ls[cur]]) {
    split(ls[cur], x);
    rs[cur] = merge(rs[ls[cur]], rs[cur]);
    trash[++tot] = ls[cur];
    ls[cur] = ls[ls[cur]];
  }
}

void reverse(int cur) {
  if(size[ls[cur]]) {
    swap(ls[cur], rs[cur]);
    reverse(ls[cur]);
    reverse(rs[cur]);
  }
}

int build(int l, int r) {
  if(l == r) return newnode(1, a[r], 0, 0);
  int mid = l + r >> 1;
  int a = build(l, mid), b = build(mid + 1, r);
  return merge(a, b);
}

int getinterval(int l, int r) {
  split(root, r);
  split(ls[root], l - 1);
  return rs[ls[root]];
}

void dispose(int cur) {
  if(size[ls[cur]]) {
    trash[++tot] = ls[cur];
    dispose(ls[cur]);
    trash[++tot] = rs[cur];
    dispose(rs[cur]);
  }
}

void dfs(int cur) {
  if(!size[ls[cur]]) v[++cnt2] = cur;
  else dfs(ls[cur]), dfs(rs[cur]);
}

int main() {
  n = read();
  for(int i = 1; i <= n; i++) a[i] = read();
  null = newnode(0, 0, 0, 0);
  root = build(0, n + 1);
  m = read();
  while(m--) {
    int opt = read(); cnt2 = 0;
    if(opt == 1) {
      int x = read() + 1, y = read();
      if(!x) root = merge(newnode(1, y, null, null), root);
      else if(x == size[root]) {
        root = merge(root, newnode(1, y, null, null));
      } else {
        split(root, x);
        ls[root] = merge(ls[root], newnode(1, y, null, null));
        update(root);
      }
    } else if(opt == 2) {
      int x = read() + 1;
      if(x == 1) {
        split(root, 1);
        root = rs[root];
      } else if(x == size[root]) {
        split(root, size[root] - 1);
        root = ls[root];
      } else {
        getinterval(x, x);
        ls[root] = ls[ls[root]];
        update(root);
      }
    } else if(opt == 3) {
      int l = read() + 1, r = read() + 1;
      reverse(getinterval(l, r));
    } else if(opt == 4) {
      int l = read() + 1, r = read() + 1, k = read();
      int cur = getinterval(l, r);
      split(cur, size[cur] - k);
      swap(ls[cur], rs[cur]);
    } else if(opt == 5) {
      int l = read() + 1, r = read() + 1, k = read();
      dfs(getinterval(l, r));
      for(int i = 1; i <= cnt2; i++) val[v[i]] += k;
    } else if(opt == 6) {
      int l = read() + 1, r = read() + 1, k = read();
      int cur = getinterval(l, r);
      dispose(cur);
      val[cur] = k;
      ls[cur] = rs[cur] = null;
    } else if(opt == 7) {
      int l = read() + 1, r = read() + 1;
      dfs(getinterval(l, r));
      ll ans = 0;
      for(int i = 1; i <= cnt2; i++)
        ans += size[v[i]] * 1LL * val[v[i]];
      printf("%lld\n", ans);
    } else if(opt == 8) {
      int l = read() + 1, r = read() + 1;
      dfs(getinterval(l, r));
      int maxnum = -2147483647, minnum = 2147483647;
      for(int i = 1; i <= cnt2; i++) {
        maxnum = max(maxnum, val[v[i]]);
        minnum = min(minnum, val[v[i]]);
      }
      printf("%d\n", maxnum - minnum);
    } else if(opt == 9) {
      int l = read() + 1, r = read() + 1, k = read();
      dfs(getinterval(l, r));
      int ans = 2147483647;
      for(int i = 1; i <= cnt2; i++)
        ans = min(ans, abs(val[v[i]] - k));
      printf("%d\n", ans);
    } else if(opt == 10) {
      int l = read() + 1, r = read() + 1, k = read();
      dfs(getinterval(l, r));
      sort(v + 1, v + cnt2 + 1, cmp);
      int cntt = 0;
      for(int i = 1; i <= cnt2; i++) {
        cntt += size[v[i]];
        if(cntt >= k) {
          printf("%d\n", val[v[i]]);
          break;
        }
      }
    } else if(opt == 11) {
      int l = read() + 1, r = read() + 1, k = read();
      dfs(getinterval(l, r));
      int ans = 0;
      for(int i = 1; i <= cnt2; i++ )
        ans += val[v[i]] < k ? size[v[i]] : 0;
      printf("%d\n", ans);
    }
  }
  return 0;
}