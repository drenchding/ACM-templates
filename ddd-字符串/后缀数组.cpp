#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1000005;
int n, sa[MAXN], rnk[MAXN], height[MAXN];
char s[MAXN];
void buildSA(int m) {
    int *x = new int[MAXN], *y = new int[MAXN], *cnt = new int[MAXN];
    for(int i = 0; i < m; i++) cnt[i] = 0;
    for(int i = 0; i < n; i++) cnt[x[i] = s[i]]++;
    for(int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
    for(int i = n - 1; i >= 0; i--) sa[--cnt[x[i]]] = i;
    for(int k = 1; k <= n; k <<= 1)
    {
        int p = 0;
        for(int i = n - k; i < n; i++) y[p++] = i;
        for(int i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
        for(int i = 0; i < m; i++) cnt[i] = 0;
        for(int i = 0; i < n; i++) cnt[x[y[i]]]++;
        for(int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for(int i = n - 1; i >= 0; i--) sa[--cnt[x[y[i]]]] = y[i];
        swap(x, y); p = 1; x[sa[0]] = 0;
        for(int i = 1; i < n; i++)
            if(y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] && sa[i] + k < n && sa[i - 1] + k < n)
                x[sa[i]] = p - 1;
            else x[sa[i]] = p++;
        if(p == n) break;
        m = p;
    }
    int k = 0;
    for(int i = 0; i < n; i++) rnk[sa[i]] = i;
    for(int i = 0; i < n; i++)
    {
        if(k != 0) k--;
        if(!rnk[i]) continue;
        int j = sa[rnk[i] - 1];
        while(s[i + k] == s[j + k]) k++;
        height[rnk[i]] = k;
    }
    delete [] x; delete [] y; delete [] cnt;
}