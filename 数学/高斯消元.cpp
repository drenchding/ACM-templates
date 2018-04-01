// a_11 + a_12 + ... + a_1n = b_1
// a_21 + a_22 + ... + a_2n = b_2
// ...
// a_n1 + a_n2 + ... + a_nn = b_n

#include <cmath>
#include <cstdio>
#include <iostream>

const int MAXN = 105;
const double eps = 1e-6;

int N;

double A[MAXN][MAXN], B[MAXN];

void swap(int x, int y) {
  double t;
  for(int i = 0; i < N; i++) t = A[x][i], A[x][i] = A[y][i], A[y][i] = t;
  t = B[x], B[x] = B[y], B[y] = t;
}

int gauss() {
  for(int j = 0; j < N; j++) {
    int k = j;
    for(int i = j; i < N; i++) {
      if(fabs(A[i][j]) > fabs(A[k][j])) k = i;
    }
    swap(j, k);
    if(fabs(A[j][j]) < eps) return 0;
    for(int i = 0; i < N; i++) if(i != j) {
      double t = A[i][j] / A[j][j];
      for(k = 0; k < N; k++) A[i][k] -= A[j][k] * t;
      B[i] -= B[j] * t;
    }
  }
  return 1;
}

int main() {
  scanf("%d", &N);
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++) {
      scanf("%lf", &A[i][j]);
    }
    scanf("%lf", &B[i]);
  }
  if(gauss()) {
    for(int i = 0; i < N; i++) {
      printf("%.2lf\n", B[i] / A[i][i]);
    }
  } else {
    puts("No Solution");
  } 
  return 0;
}