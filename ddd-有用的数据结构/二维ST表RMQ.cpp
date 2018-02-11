namespace ST {
  const int MAXL = 10;
  int LOG[MAXN], st[MAXN][MAXN][MAXL][MAXL];
  void init(int n, int m) {
    LOG[0] = -1;
    for(int i = 1; i < MAXN; i++) {
      LOG[i] = i & (i - 1) ? LOG[i - 1] : LOG[i - 1] + 1;
    }
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= m; j++) {
        st[i][j][0][0] = a[i][j];
      }
    }
    for(int i = 0; i <= LOG[n]; i++) {
      for(int j = 0; j <= LOG[m]; j++) {
        if(i == 0 && j == 0) continue; 
        for(int row = 1; row + (1 << i) - 1 <= n; row++) {
          for(int col = 1; col + (1 << j) - 1 <= m; col++) {
            if(!i) st[row][col][i][j] = max(st[row][col][i][j - 1], st[row][col + (1 << (j - 1))][i][j - 1]);
            else st[row][col][i][j] = max(st[row][col][i - 1][j], st[row + (1 << (i - 1))][col][i - 1][j]);
          }
        }
      }
    }
  }
  int queryMax(int x1, int y1, int x2, int y2) {
    int k1 = LOG[x2 - x1 + 1];
    int k2 = LOG[y2 - y1 + 1];
    int res1 = st[x1][y1][k1][k2];
    int res2 = st[x1][y2 - (1 << k2) + 1][k1][k2];
    int res3 = st[x2 - (1 << k1) + 1][y1][k1][k2];
    int res4 = st[x2 - (1 << k1) + 1][y2 - (1 << k2) + 1][k1][k2];
    return max(max(res1, res2), max(res3, res4));
  }
}