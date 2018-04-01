#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 205;
const int MOD = (int)1e9 + 7;

namespace MAT {
  int n, mat[MAXN][MAXN];
  int fexp(int a, int x) {
    int res = 1;
    while(x) {
      if(x & 1) res = 1LL * res * a % MOD;
      a = 1LL * a * a % MOD;
      x >>= 1;
    }
    return res;
  }
  int det() {
    int res = 1;
    for(int j = 1; j <= n; j++) {
      if(!mat[j][j]) {
        for(int i = j + 1; i <= n; i++) if(mat[i][j]) {
          for(int k = 1; k <= n; k++) swap(mat[i][k], mat[j][k]);
          if((i - j) & 1) res = MOD - res; break;
        }
        if(!mat[j][j]) return 0;
      }
      for(int i = j + 1; i <= n; i++) {
        if(mat[i][j]) {
          int base = 1LL * mat[j][j] * fexp(mat[i][j], MOD - 2) % MOD;
          res = 1LL * res * fexp(base, MOD - 2) % MOD;
          for(int k = 1; k <= n; k++) {
            mat[i][k] = (1LL * mat[i][k] * base % MOD - mat[j][k] + MOD) % MOD;
          }
        }
      }
    }
    for(int i = 1; i <= n; i++) res = 1LL * res * mat[i][i] % MOD;
    return res;
  }
}