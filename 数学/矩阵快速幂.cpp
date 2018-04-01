#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int MAXN = 505;
int D, MOD = 1000000007;
struct matrix {
    ll mat[MAXN][MAXN];
    int x, y;
    matrix(int A, int B) { 
        memset(mat, 0, sizeof(mat)); 
        x = A, y = B;
    }
};
matrix operator*(const matrix & mat1, const matrix & mat2) {
    if(mat1.y != mat2.x) puts("gg");
    matrix mat(mat1.x, mat2.y);
    for(int i = 1; i <= mat1.x; i++)
        for(int j = 1; j <= mat2.y; j++)
            for(int k = 1; k <= mat1.y; k++) {
                mat.mat[i][j] += mat1.mat[i][k] * mat2.mat[k][j];
                mat.mat[i][j] %= MOD;
            }
    return mat;
}
matrix pow(matrix mat, ll n) {
    if(n == 0) {
        matrix I(D, D);
        for(int i = 1; i <= D; i++)
            I.mat[i][i] = 1;
        return I;
    }
    matrix tmp = pow(mat, n / 2);
    if(n & 1) return tmp * tmp * mat;
    else return tmp * tmp;
}