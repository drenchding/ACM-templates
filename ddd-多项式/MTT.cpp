#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int MAXN = 2097152 + 5;

struct comp {
  double x, y;
  comp(): x(0), y(0) { }
  comp(const double &_x, const double &_y): x(_x), y(_y) { }
};

inline comp operator+(const comp &a, const comp &b) { 
  return comp(a.x + b.x, a.y + b.y); 
}

inline comp operator-(const comp &a, const comp &b) { 
  return comp(a.x - b.x, a.y - b.y); 
}

inline comp operator*(const comp &a, const comp &b) { 
  return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); 
}

inline comp conj(const comp &a) { 
  return comp(a.x, -a.y); 
}

const double PI = acos(-1);

int N, L;

comp w[MAXN];
int bitrev[MAXN];

void fft(comp *a, const int &n) {
  for(int i = 0; i < n; i++) if(i < bitrev[i]) swap(a[i], a[bitrev[i]]);
  for(int i = 2, lyc = n >> 1; i <= n; i <<= 1, lyc >>= 1) {
    for(int j = 0; j < n; j += i) {
      comp *l = a + j, *r = a + j + (i >> 1), *p = w;
      for(int k = 0; k < i >> 1; k++) {
        comp tmp = *r * *p;
        *r = *l - tmp, *l = *l + tmp;
        ++l, ++r, p += lyc;
      }
    }
  }
}

inline void fft_prepare() {
  for(int i = 0; i < N; i++) bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (L - 1));
  for(int i = 0; i < N; i++) w[i] = comp(cos(2 * PI * i / N), sin(2 * PI * i / N));
}

inline void conv(int *x, int *y, int *z) {
  for(int i = 0; i < N; i++) (x[i] += MOD) %= MOD, (y[i] += MOD) %= MOD;
  static comp a[MAXN], b[MAXN];
  static comp dfta[MAXN], dftb[MAXN], dftc[MAXN], dftd[MAXN];
  for(int i = 0; i < N; i++) a[i] = comp(x[i] & 32767, x[i] >> 15);
  for(int i = 0; i < N; i++) b[i] = comp(y[i] & 32767, y[i] >> 15);
  fft(a, N), fft(b, N);
  for(int i = 0; i < N; i++) {
    int j = (N - i) & (N - 1);
    static comp da, db, dc, dd;
    da = (a[i] + conj(a[j])) * comp(0.5, 0);
    db = (a[i] - conj(a[j])) * comp(0, -0.5);
    dc = (b[i] + conj(b[j])) * comp(0.5, 0);
    dd = (b[i] - conj(b[j])) * comp(0, -0.5);
    dfta[j] = da * dc;
    dftb[j] = da * dd;
    dftc[j] = db * dc;
    dftd[j] = db * dd;
  }
  for(int i = 0; i < N; i++) a[i] = dfta[i] + dftb[i] * comp(0, 1);
  for(int i = 0; i < N; i++) b[i] = dftc[i] + dftd[i] * comp(0, 1);
  fft(a, N), fft(b, N);
  for(int i = 0; i < N; i++) {
    int da = (ll)(a[i].x / N + 0.5) % MOD;
    int db = (ll)(a[i].y / N + 0.5) % MOD;
    int dc = (ll)(b[i].x / N + 0.5) % MOD;
    int dd = (ll)(b[i].y / N + 0.5) % MOD;
    z[i] = (da + ((ll)(db + dc) << 15) + ((ll)dd << 30)) % MOD;
  }
}

int main() {
  int n, m;
  static int a[MAXN], b[MAXN], c[MAXN];
  scanf("%d %d", &n, &m);
  for(int i = 0; i <= n; i++) scanf("%d", a + i);
  for(int i = 0; i <= m; i++) scanf("%d", b + i);
  for(L = 0; (1 << L) <= n + m; ++L); N = 1 << L;
  fft_prepare();
  conv(a, b, c);
  for(int i = 0; i <= n + m; i++) {
    (c[i] += MOD) %= MOD;
    printf("%d ", c[i]);
  }
  printf("\n");
  return 0;
}