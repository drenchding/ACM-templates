#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

map<int, int> mp;

int fexp(int a, int b, int c) {
  int ret = 1;
  while(b) {
    if(b & 1) ret = (ll)ret * a % c;
    a = (ll)a * a % c, b >>= 1;
  }
  return ret;
}

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int bsgs(int a, int b, int c, int d) {
  int x, y, i;
  mp.clear();
  int M = ceil(sqrt(c));
  for(x = b, i = 0; i <= M; i++, x = (ll)x * a % c) mp[x] = i;
  for(y = d, x = fexp(a, M, c), i = 1; i <= M; i++) {
    y = (ll)y * x % c;
    int tmp = mp[y];
    if(tmp) return (ll)i * M - tmp;
  }
  return -1;
}

bool not_prime[100005];

void init() {
  not_prime[1] = 1;
  for(int i = 2; i <= 100000; i++) {
    if(!not_prime[i]) {
      for(int j = i + i; j <= 100000; j += i) {
        not_prime[j] = 1;
      }
    }
  }
}

int work(int a, int b, int c) { // 求最小的 x, 使得 a ^ x = b (mod c)
  if(b == 0) {
    if(a == 0) return 1;
    init();
    map<int, int> pA, pC;
    for(int i = 1; i * i <= a; i++) {
      if(!not_prime[i]) {
        while(a % i == 0) {
          pA[i]++, a /= i;
        }
      }
    }
    if(a != 1) pA[a]++;
    for(int i = 1; i * i <= c; i++) {
      if(!not_prime[i]) {
        while(c % i == 0) {
          pC[i]++, c /= i;
        }
      }
    }
    if(c != 1) pC[c]++;
    int ans = 0;
    for(map<int, int>::iterator it = pC.begin(); it != pC.end(); it++) {
      if(!pA.count(it->first)) return -1;
      ans = max(ans, (it->second / pA[it->first]) + !!(it->second % pA[it->first]));
    }
    return ans;
  }
  int A = 1, k = 0;
  for(int i = 0; (1 << i) <= c; i++) {
    if(fexp(a, i, c) == b) {
      return i;
    }
  }
  while(1) {
    int g = gcd(a, c);
    if(g == 1) break;
    if(b % g != 0) {
      return -1;
    }
    b /= g, c /= g, A = ((ll)A * a / g) % c, k++;
  }
  int tmp = bsgs(a, b, c, A);
  if(tmp == -1) return -1;
  return tmp + k;
}