namespace BIT {
  ll c0[MAXN], c1[MAXN];
  void add(ll *c, int x, ll k) {
    for(; x <= n; x += x & -x) c[x] += k;
  }
  ll sum(ll *c, int x) { 
    ll r = 0; 
    for(; x; x -= x & -x) r += c[x];
    return r;
  }
  void add(int l, int r, ll k) {
    add(c0, l, k); add(c0, r + 1, -k);
    add(c1, l, (l - 1) * k); add(c1, r + 1, -r * k);
  }
  ll sum(int l, int r) {
    return sum(c0, r) * r - sum(c1, r) - sum(c0, l - 1) * (l - 1) + sum(c1, l - 1);
  }
}