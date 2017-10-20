#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef unsigned long long ull;
const ull base = 2333;
const int MAXN = 100005;
char s[MAXN];
ull p[MAXN], h[MAXN];
ull gethash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}
void init() {
    p[0] = 1;
    int n = strlen(s + 1);
    for(int i = 1; i <= n; i++) {
        p[i] = p[i - 1] * base;
        h[i] = h[i - 1] * base + s[i];
    }
}
int main() {
    return 0;
}