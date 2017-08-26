//bzoj3343
//第1行为两个整数N、Q。Q为问题数与教主的施法数总和。
//第2行有N个正整数，第i个数代表第i个英雄的身高。
//第3到第Q+2行每行有一个操作：
//若第一个字母为“M”，则紧接着有三个数字L、R、W。表示对闭区间 [L, R] 内所有英雄的身高加上W。
//若第一个字母为“A”，则紧接着有三个数字L、R、C。询问闭区间 [L, R] 内有多少英雄的身高大于等于C。

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1000005;
const int MAXK = 4500;
const int MAXB = 250;
const int INF = 1000000000;
int n, q, k, p, a[MAXN], bl[MAXN], st[MAXB], ed[MAXB], cnt[MAXB], tag[MAXB];
pair<int, int> b[MAXB][MAXK], c[MAXK], d[MAXK];
// 每块k个元素
// add: O(n / k + k)
// query: O((n / k)log(n / k) + klogk)
// k = sqrt(n)
void init() {
    k = (int) sqrt((double)n * log2((double)n));
    for(int i = 1; i <= n; i++) {
        bl[i] = (i - 1) / k + 1;
        if(bl[i] != bl[i - 1]) {
            st[bl[i]] = i;
            ed[bl[i - 1]] = i - 1;
        }
    }
    ed[p = bl[n]] = n;
}
void force(int l, int r, int x, int b1) {
    int t1 = 0, t2 = 0;
    for(int i = 1; i <= cnt[b1]; i++) {
        if(b[b1][i].second >= l && b[b1][i].second <= r) {
            c[++t1] = make_pair(b[b1][i].first + tag[b1] + x, b[b1][i].second);
            a[b[b1][i].second] += tag[b1] + x;
        } else {
            d[++t2] = make_pair(b[b1][i].first + tag[b1], b[b1][i].second);
            a[b[b1][i].second] += tag[b1];
        }
    }
    c[t1 + 1] = d[t2 + 1] = make_pair(INF, n + 1); 
    tag[b1] = 0;
    int p1 = 1, p2 = 1;
    for(int i = 1; i <= cnt[b1]; i++) {
        if(c[p1] < d[p2]) {
            b[b1][i] = c[p1++];
        } else {
            b[b1][i] = d[p2++];
        }
    }
}
void add(int l, int r, int x) {
    int b1 = bl[l], b2 = bl[r];
    if(b1 == b2) {
        force(l, r, x, b1);
    } else {
        force(l, ed[b1], x, b1);
        force(st[b2], r, x, b2);
        for(int i = b1 + 1; i <= b2 - 1; i++) {
            tag[i] += x;
        }
    }
}
int force(int l, int r, int x) {
    int res = 0;
    for(int i = l; i <= r; i++) {
        if(a[i] + tag[bl[i]] >= x) {
            res++;
        }
    }
    return res;
}
int calc(int l, int r, int x) {
    int b1 = bl[l], b2 = bl[r], res = 0;
    if(b1 == b2) {
        res += force(l, r, x);
    } else {
        res += force(l, ed[b1], x);
        res += force(st[b2], r, x);
        for(int i = b1 + 1; i <= b2 - 1; i++) {
            int L = 1, R = cnt[i], pos;
            while(R - L > 1) {
                int mid = (L + R) / 2;
                if(b[i][mid].first + tag[i] >= x) {
                    R = mid;
                } else {
                    L = mid;
                }
            }
            if(b[i][L].first + tag[i] >= x) {
                pos = L;
            } else if(b[i][R].first + tag[i] >= x) {
                pos = R;
            } else {
                pos = cnt[i] + 1;
            }
            res += cnt[i] - pos + 1;
        }
    }
    return res;
}
int main() {
    scanf("%d %d", &n, &q); init();
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[bl[i]][++cnt[bl[i]]] = make_pair(a[i], i);
    }
    for(int i = 1; i <= p; i++) {
        sort(b[i] + 1, b[i] + cnt[i] + 1);
    }
    while(q--) {
        char opt[3]; scanf("%s", opt);
        int l, r, x; scanf("%d %d %d", &l, &r, &x);
        if(opt[0] == 'M') {
            add(l, r, x);
        } else {
            printf("%d\n", calc(l, r, x));
        }
    }
    return 0;
}