// 余子式: 将方阵的第i行和第j列删掉,剩下的行列式称为a_{i,j}的余子式子,记为M_{i,j}
// 代数余子式: C_{i,j}=(-1)^{i+j}M_{i,j}
// 拉普拉斯展开: |A|=\sum_{i=1}^{n}a_{x,i}C_{x,i}, x表示某一行
// 伴随矩阵: 由每个元素的代数余子式构成的矩阵的转置,记作A*
// 逆矩阵: A \times inv(A) = I, A* = |A| \times inv(A)
// 求解逆矩阵: 把单位矩阵放到右边,和原矩阵一起消元
// 交换行列式两行或两列: 如果差奇数行(列), 行列式取负
// 矩阵树定理: 无向图 D[i][i]=deg[i], C[i][j]=adj[i][j], 生成树数量为(D-C)的任意一个代数余子式
// 定义一棵生成树的权值是所有边权值的乘积, 令D[i][i]=sumV[i], C[i][j]=v[i][j]即可
// 其中sumV[i]表示和i相连的所有边的权值和, v[i][j]表示i和j边的权值
// 有向图 D[i][i]=inDeg[i], C[i][j]=adj[i][j], 以i为根的生成树数量为(D-C)的C_{i,i}

typedef vector<vector<int> > Mat;

int det(Mat mat) {
  int n = mat.size(), res = 1;
  for(int j = 0; j < n; j++) {
    for(int i = j + 1; i < n && !mat[j][j]; i++) if(mat[i][j]) {
      for(int k = 0; k < n; k++) swap(mat[i][k], mat[j][k]);
      if((i - j) & 1) res = MOD - res;
    }
    if(!mat[j][j]) return 0;
    for(int i = j + 1; i < n; i++) {
      if(mat[i][j]) {
        int base = 1LL * mat[j][j] * fexp(mat[i][j], MOD - 2) % MOD;
        res = 1LL * res * fexp(base, MOD - 2) % MOD;
        for(int k = 0; k < n; k++) {
          mat[i][k] = (1LL * mat[i][k] * base % MOD - mat[j][k] + MOD) % MOD;
        }
      }
    }
  }
  for(int i = 0; i < n; i++) res = 1LL * res * mat[i][i] % MOD;
  return (res + MOD) % MOD;
}

Mat getInv(Mat mat) {
  int n = mat.size();
  Mat inv(n, vector<int>(n));
  for(int i = 0; i < n; i++) inv[i][i] = 1;
  for(int j = 0; j < n; j++) {
    for(int i = j + 1; i < n && !mat[j][j]; i++) if(mat[i][j]) {
      for(int k = 0; k < n; k++) {
        swap(mat[i][k], mat[j][k]);
        swap(inv[i][k], inv[j][k]);
      }
    }
    for(int i = j + 1; i < n; i++) {
      if(mat[i][j]) {
        int base = 1LL * mat[j][j] * fexp(mat[i][j], MOD - 2) % MOD;
        for(int k = 0; k < n; k++) {
          mat[i][k] = (1LL * mat[i][k] * base % MOD - mat[j][k] + MOD) % MOD;
          inv[i][k] = (1LL * inv[i][k] * base % MOD - inv[j][k] + MOD) % MOD;
        }
      }
    }
  }
  for(int j = n - 1; j >= 0; j--) {
    for(int i = j - 1; i >= 0; i--) {
      if(mat[i][j]) {
        int base = 1LL * mat[j][j] * fexp(mat[i][j], MOD - 2) % MOD;
        for(int k = 0; k < n; k++) {
          mat[i][k] = (1LL * mat[i][k] * base % MOD - mat[j][k] + MOD) % MOD;
          inv[i][k] = (1LL * mat[i][k] * base % MOD - inv[j][k] + MOD) % MOD;
        }
      }
    }
  }
  for(int i = 0; i < n; i++) {
    inv[i][i] = 1LL * inv[i][i] * fexp(mat[i][i], MOD - 2) % MOD;
    mat[i][i] = 1;
  }
  return inv;
}

Mat getAdj(Mat mat) {
  Mat adj = getInv(mat);
  int v = det(mat), n = mat.size();
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      adj[i][j] *= v;
    }
  }
  return adj;
}

Mat mul(const Mat & a, const Mat & b) {
  assert(a[0].size() == b.size());
  int x = a.size(), y = b[0].size();
  Mat res(x, vector<int>(y));
  for(int i = 0; i < x; i++) {
    for(int j = 0; j < y; j++) {
      for(int k = 0; k < b.size(); k++) {
        (res[i][j] += 1LL * a[i][k] * b[k][j] % MOD) %= MOD;
      }
    }
  }
  return res;
}

Mat fexp(Mat a, ll x) {
  Mat res(a.size(), vector<int>(a.size()));
  for(int i = 0; i < a.size(); i++) res[i][i] = 1;
  while(x) {
    if(x & 1) res = mul(res, a);
    a = mul(a, a);
    x >>= 1;
  }
  return res;
}