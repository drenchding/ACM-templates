/*a_11 + a_12 + ... + a_1n = b_1
  a_21 + a_22 + ... + a_2n = b_2
  ...
  a_n1 + a_n2 + ... + a_nn = b_n
解存在 b[] 里 */
int N; double A[MAXN][MAXN], B[MAXN];
int gauss() { // 返回 0 表示无解
  for(int j = 1; j <= N; j++) {
    int k = j;
    for(int i = j; i <= N; i++) {
      if(fabs(A[i][j]) > fabs(A[k][j])) k = i;
    }
    for(int i = 1; i <= N; i++) swap(A[j][i], A[k][i]);
    swap(B[j], B[k]);
    if(fabs(A[j][j]) < eps) return 0;
    for(int i = 1; i <= N; i++) if(i != j) {
      double t = A[i][j] / A[j][j];
      for(k = 1; k <= N; k++) A[i][k] -= A[j][k] * t;
      B[i] -= B[j] * t;
    }
  }
  for(int i = 1; i <= N; i++) B[i] /= A[i][i];
  return 1;
}