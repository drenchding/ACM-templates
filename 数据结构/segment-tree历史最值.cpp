//bzoj3064
//第一行一个正整数n表示序列长度
//第二行n个数表示序列初始值
//第三行一个正整数m表示操作数
//接下来每行一个操作:
//Q X Y 询问[X,Y]的最大值
//A X Y 询问[X,Y]的历史最大值
//P X Y Z [X,Y]所有数加Z
//C X Y Z [X,Y]所有数变成Z
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = 100005;
const int INF = 0x3f3f3f3f;
#define ls node<<1
#define rs node<<1|1
using namespace std;
struct Segment_Tree {
    int x, cover, add;
}s[MAXN<<2], hs[MAXN<<2];
int n, m;
inline void checkmax(int &x, int y) {
    x = max(x, y);
}
inline void h_add(int node, int v) {
    checkmax(hs[node].x, s[node].x + v);
    if(s[node].cover > -INF) {
        checkmax(hs[node].cover, s[node].cover + v);
    } else {
        checkmax(hs[node].add, s[node].add + v);
    }
}
inline void h_cover(int node, int v) {
    checkmax(hs[node].x, v);
    checkmax(hs[node].cover, v);
}
inline void m_add(int node, int v) {
    checkmax(hs[node].x, s[node].x += v);
    if(s[node].cover > -INF) {
        checkmax(hs[node].cover, s[node].cover += v);
    } else {
        checkmax(hs[node].add, s[node].add += v);
    }
}
inline void m_cover(int node, int v) {
    checkmax(hs[node].x, s[node].x = v);
    checkmax(hs[node].cover, s[node].cover = v);
    s[node].add = 0;
}
inline void pushdown(int node) {
    if(hs[node].add) {
        h_add(ls, hs[node].add);
        h_add(rs, hs[node].add);
        hs[node].add = 0;
    }
    if(hs[node].cover > -INF) {
        h_cover(ls, hs[node].cover);
        h_cover(rs, hs[node].cover);
        hs[node].cover = -INF;
    }
    if(s[node].add) {
        m_add(ls, s[node].add);
        m_add(rs, s[node].add);
        s[node].add = 0;
    }
    if(s[node].cover > -INF) {  
        m_cover(ls, s[node].cover);
        m_cover(rs, s[node].cover);
        s[node].cover = -INF;
    }
}
inline void pushup(int node) {
    s[node].x = max(s[ls].x, s[rs].x);  
    checkmax(hs[node].x, max(hs[ls].x, hs[rs].x));  
}
void build(int node, int l, int r) {
    s[node].cover = hs[node].cover = -INF;
    if(l == r) {
        scanf("%d", &s[node].x), hs[node].x = s[node].x;
        return;
    }
    int mid = l + r >> 1;
    build(ls, l, mid); build(rs, mid + 1, r);
    hs[node].x = -INF, pushup(node);
}
void add(int node, int L, int R, int l, int r, int x) {
    if(l <= L && R <= r) {
        m_add(node, x);
        return;
    }
    pushdown(node);
    int mid = L + R >> 1;
    if(l <= mid) {
        add(ls, L, mid, l, r, x);
    }
    if(r > mid) {
        add(rs, mid + 1, R, l, r, x);
    }
    pushup(node);
}
void cover(int node, int L, int R, int l, int r, int x) {
    if(l <= L && R <= r) {
        m_cover(node, x);
        return;
    }
    pushdown(node);
    int mid = L + R >> 1;
    if(l <= mid) {
        cover(ls, L, mid, l, r, x);
    }
    if(r > mid) {
        cover(rs, mid + 1, R, l, r, x);
    }
    pushup(node);
}
int query(int node, int L, int R, int l, int r) {
    if(l <= L && R <= r) {
        return s[node].x;
    }
    pushdown(node);
    int mid = L + R >> 1, ans = -INF;
    if(l <= mid) {
        ans = max(ans, query(ls, L, mid, l, r));
    }
    if(r > mid) {
        ans = max(ans, query(rs, mid + 1, R, l, r));
    }
    return ans;
}
int ask(int node, int L, int R, int l, int r) {
    if(l <= L && R <= r) {
        return hs[node].x;
    }
    pushdown(node);
    int mid = L + R >> 1, ans = -INF;
    if(l <= mid) {
        ans = max(ans, ask(ls, L, mid, l, r));
    }
    if(r > mid) {
        ans = max(ans, ask(rs, mid + 1, R, l, r));
    }
    return ans;
}
int main() {
    char opt[5];
    int i, j, k, a, b, c;
    scanf("%d", &n);
    build(1, 1, n);
    for(scanf("%d", &m); m--;) {
        scanf("%s %d %d", opt, &a, &b);
        if(opt[0] == 'Q') {
            printf("%d\n", query(1, 1, n, a, b));
        } else if(opt[0] == 'A') {
            printf("%d\n", ask(1, 1, n, a, b));
        } else if(opt[0] == 'P') {
            scanf("%d", &c);
            add(1, 1, n, a, b, c);
        } else if(opt[0] == 'C') {
            scanf("%d", &c);
            cover(1, 1, n, a, b, c);
        }
    }
    return 0;
}