namespace Hash {
  typedef long long ll;
  const ll base1 = 131;
  const ll base2 = 2333;
  const ll MOD1 = 1e9 + 7;
  const ll MOD2 = 1e9 + 9;
  const int MAXN = 100005;
  ll p1[MAXN], p2[MAXN], h1[MAXN], h2[MAXN];
  void init(char s[], int n) { // 1-based
    p1[0] = p2[0] = 1;
    h1[0] = h2[0] = 0;
    for(int i = 1; i <= n; i++) {
      p1[i] = (p1[i - 1] * base1) % MOD1;
      p2[i] = (p2[i - 1] * base2) % MOD2;
      h1[i] = (h1[i - 1] * base1 + s[i]) % MOD1;
      h2[i] = (h2[i - 1] * base2 + s[i]) % MOD2;
    }
  }
  pair<ll, ll> getHash(int l, int r) {
    ll H1 = ((h1[r] - h1[l - 1] * p1[r - l + 1]) % MOD1 + MOD1) % MOD1;
    ll H2 = ((h2[r] - h2[l - 1] * p2[r - l + 1]) % MOD2 + MOD2) % MOD2;
    return make_pair(H1, H2);
  }
}

