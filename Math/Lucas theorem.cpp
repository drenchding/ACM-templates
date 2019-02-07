namespace COMP {
  ll fac[MAXMOD], inv[MAXMOD], MOD; // 质数
  void init() {
    int i;
    for(fac[0] = 1, i = 1; i < MOD; i++)
      fac[i] = fac[i - 1] * i % MOD;
    for(inv[1] = 1, i = 2; i < MOD; i++) 
      inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    for(inv[0] = 1, i = 1; i < MOD; i++) 
      (inv[i] *= inv[i - 1]) %= MOD;
  }
  ll C(int n, int m) {
    if(n < m) return 0;
    if(n < MOD && m < MOD) {
      return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
    }
    return C(n / MOD, m / MOD) * C(n % MOD, m % MOD) % MOD;
  }
}
