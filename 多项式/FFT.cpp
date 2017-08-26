#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const int MAXN = 262144;
const double PI = M_PI;
int g[MAXN];
struct Complex {    
    double a, b;    
    Complex() {}    
    Complex(double A, double B) : a(A), b(B){}
    void operator+=(const Complex & x) {    
        a += x.a;  
        b += x.b;  
    }
    Complex operator-(const Complex & x) const {
        return Complex(a - x.a, b - x.b);    
    }
    Complex operator*(const Complex & x) const {
        return Complex(a * x.a - b * x.b, a * x.b + b * x.a);    
    }
    void operator*=(const Complex & x) {
        *this = (*this) * x;    
    }
    Complex operator+(const Complex & x) {
        Complex re = *this;  
        re += x; return re;  
    }
}a[MAXN], b[MAXN], c[MAXN];
void DFT(Complex *a, int f, int N) {
    for(int i = 0; i < N; i++) {
        if(g[i] > i) {
            swap(a[i], a[g[i]]);
        }
    }
    for(int i = 1; i < N; i <<= 1) {
        Complex e(cos(PI / i), f * sin(PI / i));
        for(int j = 0; j < N; j += i << 1) {
            Complex w(1, 0);
            for(int k = 0; k < i; k++, w *= e) {
                Complex x = a[j + k];
                Complex y = w * a[j + k + i];
                a[j + k] = x + y; 
                a[j + k + i] = x - y;
            }
        }
    }
    if(f != 1) for(int i = 0; i < N; i++) {
        a[i].a /= N;
    }
}
void FFT(Complex *a, Complex *b, int n) {
    int t = -1, N;
    for(N = 1; N <= n; N <<= 1, t++);
    for(int i = 1; i < N; i++) {
        g[i] = (g[i >> 1] >> 1) | ((i & 1) << t);
    }
    DFT(a, 1, N); DFT(b, 1, N);
    for(int i = 0; i < N; i++) {
        c[i] = a[i] * b[i];
    }
    DFT(c, -1, N);
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i <= n; i++) {
        int x; scanf("%d", &x);
        a[i] = Complex((double)x, 0);
    }
    for(int i = 0; i <= m; i++) {
        int x; scanf("%d", &x);
        b[i] = Complex((double)x, 0);
    }
    FFT(a, b, n + m);
    for(int i = 0; i <= n + m; i++) {
        printf("%d ", (int)(c[i].a + 0.5));
    }
    putchar('\n');
    return 0;
}