// https://www.zybuluo.com/Drench/note/774721

#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> Poly;

namespace FFT {
  const double PI = acos(-1);
   
  struct Comp {
    double x, y;
    Comp(double X = 0, double Y = 0): x(X), y(Y) { }
    friend Comp operator+(const Comp & a, const Comp & b) {
      return Comp(a.x + b.x, a.y + b.y);
    }
    friend Comp operator-(const Comp & a, const Comp & b) {
      return Comp(a.x - b.x, a.y - b.y);
    }
    friend Comp operator*(const Comp & a, const Comp & b) {
      return Comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }
    friend Comp operator!(const Comp & a) {
      return Comp(a.x, -a.y);
    }
  }*w;
 
  void dft(Comp *a, int n) {
    for(int i = 0, j = 0; i < n; i++) {
      if(i > j) swap(a[i], a[j]);
      for(int k = n >> 1; (j ^= k) < k; k >>= 1);
    }
    for(int i = 2, b = n >> 1; i <= n; i <<= 1, b >>= 1) {
      for(int j = 0; j < n; j += i) {
        Comp *l = a + j, *r = a + j + (i >> 1), *p = w;
        for(int k = 0; k < (i >> 1); k++) {
          Comp t = *r * *p;
          *r = *l - t, *l = *l + t;
          l++, r++, p += b;
        }
      }
    }
  }

  void conv(Poly x, Poly y, Poly & z) {
    if(x.size() == 1 && y.size() == 1) {
      z.resize(1); z[0] = x[0] * y[0]; return;
    }
    int t = 0, n = x.size() + y.size() - 1;
    while((1 << t) < n) t++;
    n = (1 << (--t));
    Comp step = Comp(cos(2 * PI / n), sin(2 * PI / n));
    Comp *a = new Comp[n], *b = new Comp[n], *c = new Comp[n];
    w = new Comp[n];
    w[0] = Comp(1, 0);
    for(int i = 0; i < n - 1; i++) w[i + 1] = w[i] * step;
    for(int i = 0; i < n; i++) {
      a[i].x = (i << 1) < x.size() ? x[i << 1] : 0;
      b[i].x = (i << 1) < y.size() ? y[i << 1] : 0;
      a[i].y = (i << 1 | 1) < x.size() ? x[i << 1 | 1] : 0;
      b[i].y = (i << 1 | 1) < y.size() ? y[i << 1 | 1] : 0;
    }
    dft(a, n); dft(b, n);
    for(int i = 0; i < n; i++) {
      int j = (n - i) & (n - 1);
      c[i] = (Comp(4, 0) * !(a[j] * b[j]) - 
             (!a[j] - a[i]) * (!b[j] - b[i]) * 
             (w[i] + Comp(1, 0))) * Comp(0, 0.25);
    }
    reverse(w + 1, w + n); dft(c, n);
    int d = ((x.size() + y.size() - 1) >> 1) + 1;
    z.resize(d << 1);
    for(int i = 0; i < d; i++) {
      z[i << 1] = c[i].y / n + 0.5;
      z[i << 1 | 1] = c[i].x / n + 0.5;
    }
    delete[] w; delete[] a; delete[] b; delete[] c;
  }
}

namespace MTT {
  const double PI = acos(-1);
  const int MOD = 1e9 + 7;
  
  struct Comp {
    double x, y;
    Comp(double X = 0, double Y = 0): x(X), y(Y) { }
    friend Comp operator+(const Comp & a, const Comp & b) {
      return Comp(a.x + b.x, a.y + b.y);
    }
    friend Comp operator-(const Comp & a, const Comp & b) {
      return Comp(a.x - b.x, a.y - b.y);
    }
    friend Comp operator*(const Comp & a, const Comp & b) {
      return Comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }
    friend Comp operator!(const Comp & a) {
      return Comp(a.x, -a.y);
    }
  }*w;

  int fexp(int a, int b) {
    int res = 1;
    for(int i = 1; i <= b; i <<= 1) {
      if(i & b) res = res * (ll)a % MOD;
      a = a * (ll)a % MOD;
    }
    return res;
  }

  void dft(Comp *a, int n) {
    for(int i = 0, j = 0; i < n; i++) {
      if(i > j) swap(a[i], a[j]);
      for(int k = n >> 1; (j ^= k) < k; k >>= 1);
    }
    for(int i = 2, b = n >> 1; i <= n; i <<= 1, b >>= 1) {
      for(int j = 0; j < n; j += i) {
        Comp *l = a + j, *r = a + j + (i >> 1), *p = w;
        for(int k = 0; k < (i >> 1); k++) {
          Comp t = *r * *p;
          *r = *l - t, *l = *l + t;
          l++, r++, p += b;
        }
      }
    }
  }

  void conv(Poly x, Poly y, Poly & z) {
    int t = 0, n = x.size() + y.size() - 1;
    while((1 << t) < n) t++;
    n = (1 << t);
    x.resize(n); y.resize(n);
    w = new Comp[n]; 
    Comp *a = new Comp[n], *b = new Comp[n];
    for(int i = 0; i < n; i++) {
      w[i] = Comp(cos(2 * PI * i / n), sin(2 * PI * i / n));
      (x[i] += MOD) %= MOD; (y[i] += MOD) %= MOD;
      a[i] = Comp(x[i] & 32767, x[i] >> 15);
      b[i] = Comp(y[i] & 32767, y[i] >> 15);
    }
    dft(a, n); dft(b, n);
    Comp *dfta = new Comp[n], *dftb = new Comp[n];
    Comp *dftc = new Comp[n], *dftd = new Comp[n];
    for(int i = 0; i < n; i++) {
      int j = (n - i) & (n - 1);
      static Comp da, db, dc, dd;
      da = (a[i] + !a[j]) * Comp(0.5, 0);
      db = (a[i] - !a[j]) * Comp(0, -0.5);
      dc = (b[i] + !b[j]) * Comp(0.5, 0);
      dd = (b[i] - !b[j]) * Comp(0, -0.5);
      dfta[j] = da * dc;
      dftb[j] = da * dd;
      dftc[j] = db * dc;
      dftd[j] = db * dd;
    }
    for(int i = 0; i < n; i++) {
      a[i] = dfta[i] + dftb[i] * Comp(0, 1);
      b[i] = dftc[i] + dftd[i] * Comp(0, 1);
    }
    dft(a, n); dft(b, n);
    z.resize(n);
    for(int i = 0; i < n; i++) {
      int da = (ll)(a[i].x / n + 0.5) % MOD;
      int db = (ll)(a[i].y / n + 0.5) % MOD;
      int dc = (ll)(b[i].x / n + 0.5) % MOD;
      int dd = (ll)(b[i].y / n + 0.5) % MOD;
      z[i] = (da + ((ll)(db + dc) << 15) + ((ll)dd << 30)) % MOD;
    }
    delete[] w; delete[] a; delete[] b;
    delete[] dfta; delete[] dftb; 
    delete[] dftc; delete[] dftd;
  }
}
 
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

namespace Newton {
  using namespace MTT;

  void getInv(Poly a, Poly & b, int N) { // a * b = 1 (mod x ^ N)
    if(N == 1) {
      b.resize(1);
      b[0] = fexp(a[0], MOD - 2);
    } else {
      a.resize(N);
      getInv(a, b, (N + 1) / 2);
      Poly c;
      conv(a, b, c);
      c.resize(N);
      for(int i = 0; i < N; i++) {
        c[i] = (MOD - c[i]) % MOD;
      }
      c[0] = (c[0] + 2) % MOD;
      conv(b, c, b);
      b.resize(N);
    }
  }

  void getBernoulli(Poly & a, int N) { // get Bernoulli Number [0, N]
    Poly F(N + 1);
    vector<int> fac(N + 2);
    fac[0] = 1;
    for(int i = 0; i <= N; i++) {
      fac[i + 1] = fac[i] * (ll)(i + 1) % MOD;
      F[i] = fexp(fac[i + 1], MOD - 2);
    }
    getInv(F, a, N + 1);
    for(int i = 0; i <= N; i++) {
      a[i] = a[i] * (ll)fac[i] % MOD;
    }
    a[1] = MOD - a[1];
  }
}