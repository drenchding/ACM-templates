//Luogu3710
//二维矩形修改, 单点查询
//第一行两个整数n, m, 分别表示序列长度和操作个数
//接下来是m个操作:
//1 l r d 把[l,r]所有数加d
//2 l r d 把[l,r]所有数乘d
//3 p 询问位置为p的数%998244353
//3 撤销第p行的操作
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 150005;
const int MOD = 998244353;
inline int read() {
    int x = 0; char ch;
    while(ch = getchar(), !isdigit(ch));
    while(x = x * 10 + ch - '0', ch = getchar(), isdigit(ch));
    return x;
}
int nd, n, m, root, cnt, addv[MAXN], mulv[MAXN], val[MAXN];
struct node {
    int Mx[2], Mn[2], D[2], ch[2];
}a[MAXN];
struct qqq { 
    int op, l, r, d, i, j; 
}Q[MAXN];
bool cmp(const node &a, const node &b) {
    return a.D[nd] == b.D[nd] ? a.D[nd ^ 1] < b.D[nd ^ 1] : a.D[nd] < b.D[nd];
}
void update(int cur) {
    a[cur].Mx[0] = a[cur].Mn[0] = a[cur].D[0];
    a[cur].Mx[1] = a[cur].Mn[1] = a[cur].D[1];
    for(int i = 0; i < 2; i++) {
        if(a[cur].ch[i]) {
            node *v = a + a[cur].ch[i];
            for(int j = 0;j <= 1; j++) {
                a[cur].Mx[j] = max(a[cur].Mx[j], v->Mx[j]);
                a[cur].Mn[j] = min(a[cur].Mn[j], v->Mn[j]);
            }
        }
    }
}
int build(int l, int r, int D) {
    nd = D; int mid = (l + r) >> 1;
    nth_element(a + l, a + mid, a + r + 1, cmp);
    if(l < mid) {
        a[mid].ch[0] = build(l, mid - 1, D ^ 1);
    }
    if(r > mid) {
        a[mid].ch[1] = build(mid + 1, r, D ^ 1);
    }
    update(mid); return mid;
}
inline void mul(int cur, int v1, int v2) {
    val[cur] = (1LL * val[cur] * v1 + v2) % MOD;
    mulv[cur] = 1LL * mulv[cur] * v1 % MOD;
    addv[cur] = (1LL * addv[cur] * v1 + v2) % MOD;
}
inline void pushdown(int cur) {
    if(mulv[cur] == 1 && addv[cur] == 0) {
        return;
    }
    for(int i = 0; i < 2; i++) {
        if(a[cur].ch[i]) {
            mul(a[cur].ch[i], mulv[cur], addv[cur]);
        }
    }
    mulv[cur] = 1; addv[cur] = 0;
}
inline bool in(int cur,int v) {
    return a[cur].Mx[0] <= Q[v].j && a[cur].Mn[0] >= Q[v].i && a[cur].Mx[1] <= Q[v].r && a[cur].Mn[1] >= Q[v].l;
}
inline bool out(int cur,int v) {
    return a[cur].Mx[0] < Q[v].i || a[cur].Mn[0] > Q[v].j || a[cur].Mx[1] < Q[v].l || a[cur].Mn[1] > Q[v].r;
}
inline bool pointin(int cur,int v) {
    return a[cur].D[0] <= Q[v].j && a[cur].D[0] >= Q[v].i && a[cur].D[1] <= Q[v].r && a[cur].D[1] >= Q[v].l;
}
void change(int cur, int id, int v1, int v2) {
    if(in(cur, id)) {
        mul(cur, v1, v2);
        return;
    }
    pushdown(cur);
    if(pointin(cur, id)) {
        mul(cur, v1, v2);
        mulv[cur] = 1; 
        addv[cur] = 0;
    }
    for(int i = 0; i < 2; i++) {
        if(!out(a[cur].ch[i], id)) {
            change(a[cur].ch[i], id, v1, v2);
        }
    }
}
int query(int cur, int qx, int qy, int dd) {
    pushdown(cur);
    if(qx == a[cur].D[0] && qy == a[cur].D[1]) {
        return val[cur];
    }
    if(!dd) {
        return query(a[cur].ch[a[cur].D[0] < qx], qx, qy, dd ^ 1);
    } else {
        if(a[cur].D[1] == qy) {
            return query(a[cur].ch[a[cur].D[0] < qx], qx, qy, dd ^ 1);
        }
        return query(a[cur].ch[a[cur].D[1] < qy], qx, qy, dd ^ 1);       
    }
}
int main() {
    n = read(); m = read();
    for(int i = 1; i <= m; i++) {
        Q[i].op = read();
        if(Q[i].op == 3) {
            Q[i].d = read();
            a[++cnt].D[0] = i;
            a[cnt].D[1] = Q[i].d;
        } else if(Q[i].op == 4) {
            Q[i].d = read();
            Q[Q[i].d].j = i;
        } else {
            Q[i].l = read(); Q[i].r = read(); Q[i].d = read();
            Q[i].i = i; Q[i].j = m;
        }
    }
    root = build(1, cnt, 0);
    for(int i = 1; i <= cnt; i++) {
        mulv[i] = 1;
    }
    for(int i = 1; i <= m; i++) {
        if(Q[i].op == 3) {
            printf("%d\n",query(root, i, Q[i].d, 0));
        } else if(Q[i].op == 1) {
            change(root, i, 1, Q[i].d);
        } else if(Q[i].op == 2) {
            change(root, i, Q[i].d, 0);
        }
    }
    return 0;
}