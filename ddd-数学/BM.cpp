#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;

ll MOD = 1e9 + 7;

namespace linear_seq {
  const int LMAXN = 10010;
  ll res[LMAXN], base[LMAXN], _c[LMAXN], _md[LMAXN];
  vector<ll> Md;

  ll pw(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    for(; b; b >>= 1) {
      if(b & 1) res = res * a % MOD;
      a = a * a % MOD;
    }
    return res;
  }

  void mul(ll *a, ll *b, ll k) {
    for(int i = 0; i < k + k; i++) _c[i] = 0;
    for(int i = 0; i < k; i++) if(a[i]) {
      for(int j = 0; j < k; j++) {
        _c[i + j] = (_c[i + j] + a[i] * b[j]) % MOD;
      }
    }
    for(int i = k + k - 1; i >= k; i--) if(_c[i]) {
      for(int j = 0; j < (int)Md.size(); j++) {
        _c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % MOD;
      }
    }
    for(int i = 0; i < k; i++) a[i] = _c[i];
  }

  ll solve(ll n, vector<ll> a, vector<ll> b) {
    ll ans = 0, pnt = 0;
    int k = a.size();
    for(int i = 0; i < k; i++) {
      _md[k - 1 - i] = -a[i];
    }
    _md[k] = 1;
    Md.clear();
    for(int i = 0; i < k; i++) if(_md[i]) {
      Md.push_back(i);
    }
    for(int i = 0; i < k; i++) res[i] = base[i] = 0;
    res[0] = 1;
    while((1LL << pnt) <= n) pnt++;
    for(int p = pnt; p >= 0; p--) {
      mul(res, res, k);
      if((n >> p) & 1) {
        for(int i = k - 1; i >= 0; i--) {
          res[i + 1] = res[i];
        }
        res[0] = 0;
        for(int j = 0; j < (int)Md.size(); j++) {
          res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % MOD;
        }
      }
    }
    for(int i = 0; i < k; i++) {
      ans = (ans + res[i] * b[i]) % MOD;
    }
    if(ans < 0) ans += MOD;
    return ans;
  }

  vector<ll> BM(vector<ll> s) {
    vector<ll> C(1, 1), B(1, 1);
    ll L = 0, m = 1, b = 1;
    for(int n = 0; n < (int)s.size(); n++) {
      ll d = 0;
      for(int i = 0; i < L + 1; i++) {
        d = (d + C[i] * s[n - i]) % MOD;
      }
      if(!d) ++m;
      else if(2 * L <= n) {
        vector<ll> T = C;
        ll c = MOD - d * pw(b, MOD - 2) % MOD;
        while(C.size() < B.size() + m) C.push_back(0);
        for(int i = 0; i < (int)B.size(); i++) {
          C[i + m] = (C[i + m] + c * B[i]) % MOD;
        }
        L = n + 1 - L; B = T; b = d; m = 1;
      } else {
        ll c = MOD - d * pw(b, MOD - 2) % MOD;
        while(C.size() < B.size() + m) C.push_back(0);
        for(int i = 0; i < (int)B.size(); i++) {
          C[i + m] = (C[i + m] + c * B[i]) % MOD;
        }
        ++m;
      }
    }
    return C;
  }

  ll work(vector<ll> a, ll n) {
    vector<ll> c = BM(a);
    c.erase(c.begin());
    for(int i = 0; i < (int)c.size(); i++) {
      c[i] = (MOD - c[i]) % MOD;
    }
    return solve(n, c, vector<ll>(a.begin(), a.begin() + c.size()));
  }
}