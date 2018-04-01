namespace ST {
  const int MAXN = 1000005;
  int n, a[MAXN], lg2[MAXN], mx[21][MAXN];
  inline void chkmax(int &a, int b) {
     if(b > a) a = b;
  }
  inline int max(int a, int b) {
    return a > b ? a : b;
  }
  inline void rmq_init() { 
    for(int i = 2; i <= n; i++) {
      lg2[i] = lg2[i >> 1] + 1;
    }
    for(int i = 1; i <= n; i++) {
      mx[0][i] = a[i];
    }
    int m = lg2[n];
    for(int i = 1; i <= m; i++) {
      for(int j = n; j >= 1; j--) {
        mx[i][j] = mx[i - 1][j];
        if(j + (1 << (i - 1)) <= n) {
          chkmax(mx[i][j], mx[i - 1][j + (1 << (i - 1))]);
        }
      }
    }
  }
  inline int query(int l, int r) {
    int m = lg2[r - l + 1];
    return max(mx[m][l], mx[m][r - (1 << m) + 1]);
  }
}