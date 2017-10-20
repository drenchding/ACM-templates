// [1, n] 的素数个数

#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

ll prime_count(ll n) {
  const ll v = static_cast<ll>(sqrt(n));
  vector<ll> ssum(v + 1), lsum(v + 1);
  vector<bool> mark(v + 1);
  for(int i = 1; i <= v; ++i) {
    ssum[i] = i - 1;
    lsum[i] = n / i - 1;
  }
  for(ll p = 2; p <= v; ++p) {
    if(ssum[p] == ssum[p - 1]) continue;
    ll psum = ssum[p - 1], q = p * p, ed = min(v, n / q);
    int delta = (p & 1) + 1;
    for(int i = 1; i <= ed; i += delta) if(!mark[i]) {
      ll d = i * p;
      if(d <= v) {
        lsum[i] -= lsum[d] - psum;
      } else {
        lsum[i] -= ssum[n / d] - psum;
      }
    }
    for(ll i = q; i <= ed; i += p * delta) mark[i] = true;
    for(ll i = v; i >= q; --i) {
      ssum[i] -= ssum[i / p] - psum;
    }
  }
  return lsum[1];
}

int main() {
  ll n;
  scanf("%lld", &n);
  printf("%lld\n", prime_count(n));
  return 0;
}