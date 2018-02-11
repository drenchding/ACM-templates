#include <cmath>
#include <vector>

using namespace std;

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
  };

  typedef vector<Comp> Poly;

  void dft(Poly & a, int f) {
    int n = a.size();
    for(int i = 0, j = 0; i < n; i++) {
      if(i > j) swap(a[i], a[j]);
      for(int k = n >> 1; (j ^= k) < k; k >>= 1);
    }
    for(int i = 1; i < n; i <<= 1) {
      Comp e(cos(PI / i), f * sin(PI / i));
      for(int j = 0; j < n; j += (i << 1)) {
        Comp w(1, 0);
        for(int k = 0; k < i; k++, w = w * e) {
          Comp x = a[j + k], y = w * a[i + j + k];
          a[j + k] = x + y, a[i + j + k] = x - y;
        }
      }
    }
    if(f == -1) for(int i = 0; i < n; i++) {
      a[i].x /= n, a[i].y /= n;
    }
  }

  void conv(Poly & a, Poly & b, Poly & c) {
    int t = -1, n = a.size() + b.size() - 2;
    while(n >= (1 << (t + 1))) t++;
    n = (1 << (t + 1));
    a.resize(n); b.resize(n); c.resize(n);
    dft(a, 1); dft(b, 1);
    for(int i = 0; i < n; i++) c[i] = a[i] * b[i];
    dft(c, -1);
  }
}

namespace NTT {
  typedef long long ll;
  typedef vector<int> Poly;

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

  int fexp(int a, int b) {
    int res = 1;
    for(int i = 1; i <= b; i <<= 1) {
      if(i & b) res = res * (ll)a % MOD;
      a = a * (ll)a % MOD;
    }
    return res;
  }

  void dft(Poly & a, int f) {
    int n = a.size();
    for(int i = 0, j = 0; i < n; i++) {
      if(i > j) swap(a[i], a[j]);
      for(int k = n >> 1; (j ^= k) < k; k >>= 1);
    }
    int g = fexp(G, R);
    for(int i = 1, b = 1; i < n; i <<= 1, b++) {
      int e = fexp(g, 1 << (DEG - b));
      if(f < 0) e = fexp(e, MOD - 2);
      for(int j = 0; j < n; j += i << 1) {
        int w = 1;
        for(int k = 0; k < i; k++, w = w * (ll)e % MOD) {
          int x = a[j + k], y = w * (ll)a[j + k + i] % MOD;
          a[j + k] = x + y, a[j + k + i] = x - y;
          if(a[j + k] >= MOD) a[j + k] -= MOD;
          if(a[j + k + i] < 0) a[j + k + i] += MOD;
        }
      }
    }
    if(f < 0) {
      int v = fexp(n, MOD - 2);
      for(int i = 0; i < n; i++) {
        a[i] = a[i] * (ll)v % MOD;
      }
    }
  }

  void conv(Poly & a, Poly & b, Poly & c) {
    int t = -1, n = a.size() + b.size() - 2;
    while(n >= (1 << (t + 1))) t++;
    n = (1 << (t + 1));
    a.resize(n); b.resize(n); c.resize(n);
    dft(a, 1); dft(b, 1);
    for(int i = 0; i < n; i++) c[i] = a[i] * (ll)b[i] % MOD;
    dft(c, -1);
  }
}