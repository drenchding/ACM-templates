#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 205;
const int MOD = (int)1e9 + 7;

namespace Comp {
  const int MAXK = 200005;
  int fac[MAXK], inv[MAXK];
  void init() {
    fac[0] = inv[0] = inv[1] = 1;
    for(int i = 2; i < MAXK; i++) {
      inv[i] = 1LL * (MOD - (MOD / i)) * inv[MOD % i] % MOD;
    }
    for(int i = 1; i < MAXK; i++) {
      fac[i] = 1LL * fac[i - 1] * i % MOD;
      inv[i] = 1LL * inv[i - 1] * inv[i] % MOD;
    }
  }
  int C(int n, int k) {
    return 1LL * fac[n] * inv[k] % MOD * inv[n - k] % MOD;
  }
}