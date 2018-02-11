#include <set>
#include <cstdio>
#include <climits>
#include <iostream>

using namespace std;

typedef set<pair<int, int> >::iterator SI;

const int MAXN = 100005;

struct Point {
  int x, y;
}P[MAXN];

int main() {
  int n;
  scanf("%d", &n);
  set<pair<int, int > > S[2], T[2];
  for(int i = 1; i <= n; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    P[i].x = x + y;
    P[i].y = x - y;
    if(i == 1) {
      S[0].insert(make_pair(P[i].x, i));
      S[1].insert(make_pair(P[i].y, i));
    } else {
      T[0].insert(make_pair(P[i].x, i));
      T[1].insert(make_pair(P[i].y, i));
    }
  }
  long long ans = 0;
  while(!T[0].empty()) {
    int maxV = -INT_MAX;
    int u = -1, v = -1;
    for(int i = 0; i < 2; i++) {
      SI minA = S[i].begin();
      SI maxA = S[i].end(); maxA--;
      SI minB = T[i].begin();
      SI maxB = T[i].end(); maxB--;
      if(maxA->first - minB->first > maxV) {
        maxV = maxA->first - minB->first;
        u = maxA->second, v = minB->second;
      }
      if(maxB->first - minA->first > maxV) {
        maxV = maxB->first - minA->first;
        u = minA->second, v = maxB->second;
      }
    }
    for(int i = 0; i < 2; i++) {
      pair<int, int> p;
      if(!i) p = make_pair(P[v].x, v);
      else p = make_pair(P[v].y, v);
      S[i].insert(p);
      T[i].erase(p);
    }
    ans += maxV;
  }
  printf("%d\n", ans);
  return 0;
}