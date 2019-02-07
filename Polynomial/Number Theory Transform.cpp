typedef long long ll;
typedef vector<int> Poly;
namespace NTT {
  /*
  MOD = 167772161, R: 5, DEG: 25, G: 3
  MOD = 469762049, R: 7, DEG: 26, G: 3
  MOD = 754974721, R: 45, DEG: 24, G: 11
  MOD = 998244353, R: 119, DEG: 23, G: 3
  MOD = 1107296257, R: 33, DEG: 25, G: 10
  MOD = 99857989633, R: 93, DEG: 30, G: 2
  MOD = 110595407873, R: 103, DEG: 30, G: 2
  MOD = 970662608897, R: 113, DEG: 33, G: 2
  MOD = 1009317314561, R: 235, DEG: 32, G: 2
  MOD = 12025908428801, R: 175, DEG: 36, G: 2
  MOD = 98406290685953, R: 179, DEG: 39, G: 2
  MOD = 106652627894273, R: 97, DEG: 40, G: 2
  */
  const int R = 119, DEG = 23, G = 3;
  const int MOD = R * (1 << DEG) + 1;
  int *w;
  int fexp(int a, int b) {
    int res = 1;
    for(int i = 1; i <= b; i <<= 1) {
      if(i & b) res = res * (ll)a % MOD;
      a = a * (ll)a % MOD;
    }
    return res;
  }
  void dft(Poly & a) {
    int n = a.size();
    for(int i = 0, j = 0; i < n; i++) {
      if(i > j) swap(a[i], a[j]);
      for(int k = n >> 1; (j ^= k) < k; k >>= 1);
    }
    for(int i = 1, b = n >> 1; i < n; i <<= 1, b >>= 1) {
      for(int j = 0; j < n; j += (i << 1)) {
        for(int k = 0; k < i; k++) {
          int s = a[j + k], t = a[j + k + i] * (ll)w[b * k] % MOD;
          a[j + k] = s + t, a[j + k + i] = s - t;
          if(a[j + k] > MOD) a[j + k] -= MOD;
          if(a[j + k + i] < 0) a[j + k + i] += MOD; 
        }
      }
    }
  }
  void prepare(int n) {
    int step = fexp(G, (MOD - 1) / n);
    w = new int[n];
    w[0] = 1;
    for(int i = 1; i < n; i++) {
      w[i] = w[i - 1] * (ll)step % MOD;
    }
  }
  void conv(Poly a, Poly b, Poly & c) {
    int t = 0, n = a.size() + b.size() - 1;
    while((1 << t) < n) t++;
    n = (1 << t);
    a.resize(n); b.resize(n); c.resize(n);
    prepare(n); dft(a); dft(b);
    for(int i = 0; i < n; i++) {
      c[i] = a[i] * (ll)b[i] % MOD;
    }
    reverse(w + 1, w + n); dft(c);
    int inv = fexp(n, MOD - 2);
    for(int i = 0; i < n; i++) {
      c[i] = c[i] * (ll)inv % MOD;
    }
    delete[] w;
  }
}