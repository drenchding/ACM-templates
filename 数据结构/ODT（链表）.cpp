// 给定一个长度为 n 的非负整数序列 a_1, a_2, ..., a_n, 你需要支持以下三种类型的操作：
// 1. 区间平方取模
// 2. 区间cover
// 3. 区间数字种数

#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 400005;

int n, m, cnt, cnt2, head;
int nxt[MAXN], l[MAXN], r[MAXN], val[MAXN], odt[MAXN], vis[MAXN];

int newnode(int x, int y, int nx, int v) {
  int cur = ++cnt;
  l[cur] = x, r[cur] = y;
  nxt[cur] = nx, val[cur] = v;
  return cur;
}

int split(int x, int y) {
  int cur = head;
  int left = 0;
  while(nxt[cur]) {
    cur = nxt[cur];
    if(x == l[cur]) left = cur;
    if(x > l[cur] && x <= r[cur]) {
      nxt[cur] = newnode(x, r[cur], nxt[cur], val[cur]);
      r[cur] = x - 1;
      left = nxt[cur];
    }
    if(y >= l[cur] && y < r[cur]) {
      nxt[cur] = newnode(y + 1, r[cur], nxt[cur], val[cur]);
      r[cur] = y;
      break;
    }
  }
  return left;
}

void cover(int x, int y, int v) {
  int cur = split(x, y);
  int curr = cur;
  while(r[curr] != y) curr = nxt[curr];
  nxt[cur] = nxt[curr];
  r[cur] = y;
  val[cur] = v;
}

void square(int x, int y) {
  int cur = split(x, y);
  int curr = cur;
  val[curr] = (val[curr] * val[curr]) % 2017;
  while(r[curr] != y) {
    curr = nxt[curr];
    val[curr] = (val[curr] * val[curr]) % 2017;
  }
}

void drive(int x, int y) {
  int cur = split(x, y);
  int curr = cur;
  cnt2 = 0;
  odt[++cnt2] = curr;
  while(r[curr] != y) {
    curr = nxt[curr];
    odt[++cnt2] = curr;
  }
}

int main() {
  int T; scanf("%d", &T);
  while(T--) {
    cnt = head = 0;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) {
      scanf("%d", &val[i]);
      nxt[i - 1] = i;
      l[i] = r[i] = i;
    }
    nxt[n] = 0; cnt = n;
    while(m--) {
      int opt, x, y;
      scanf("%d %d %d", &opt, &x, &y);
      if(opt == 1) square(x, y);
      else if(opt == 2) {
        int k; scanf("%d", &k);
        cover(x, y, k);
      } else {
        int res = 0;
        drive(x, y);
        for(int i = 1; i <= cnt2; i++) {
          if(!vis[val[odt[i]]]) {
            res++, vis[val[odt[i]]] = 1;
          }
        }
        for(int i = 1; i <= cnt2; i++)
          vis[val[odt[i]]] = 0;
        printf("%d\n", res);
      }
    }
  }
  return 0;
}