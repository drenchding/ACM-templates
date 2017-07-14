//bzoj4515
//树上路径线段覆盖, 最值查询
//第一行两个数n, m, 表示点数和操作数
//接下来n-1行表示一棵树
//接下来m行表示操作:
//1 s t a b 将s->t的路径上的每个点加某值, 对于路径上的一个点r, 若r与s的距离是dis, 那么加的是a*dis+b
//2 s t 查询s->t的min
#include <cstdio>
#include <cstring>
#include <iostream>
typedef long long ll;
using namespace std;  
const int MAXN = 100005;
const ll INF = 123456789123456789LL;
int n, m, tot, cnt, fst[MAXN];
int pnt[MAXN<<1], len[MAXN<<1], nxt[MAXN<<1], lk[MAXN<<2];
int fa[MAXN], son[MAXN], size[MAXN], top[MAXN], dfn[MAXN], dfm[MAXN];  
ll lb[MAXN<<2], val[MAXN<<2], d[MAXN], ans; 
bool tag[MAXN<<2];  
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(!isdigit(ch)) { 
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(isdigit(ch)) { 
        x = x * 10 + ch - '0';
        ch = getchar(); 
    }
    return x * f;
} 
void add(int x, int y, int z) {  
    pnt[++tot] = y; len[tot] = z; nxt[tot] = fst[x]; fst[x] = tot;  
}  
void dfs(int x) {  
    int p; size[x] = 1;  
    for(p = fst[x]; p; p = nxt[p]) {  
        int y = pnt[p];  
        if(fa[x] != y) {  
            fa[y] = x; 
            d[y] = d[x] + len[p];  
            dfs(y); size[x] += size[y];  
            if(size[y] > size[son[x]]) {
                son[x]=y;
            }
        }  
    }  
}  
void dfs2(int x, int tp)
{  
    dfn[x] = ++cnt; 
    dfm[cnt] = x; 
    top[x] = tp;  
    if(son[x]) {
        dfs2(son[x],tp); int p;  
        for(p = fst[x]; p; p = nxt[p]) {  
            int y = pnt[p]; 
            if(y != fa[x] && y != son[x]) {
                dfs2(y, y);  
            }
        }
    }
}  
int lca(int x, int y) {  
    for(; top[x] != top[y]; x = fa[top[x]]) {
        if(d[top[x]] < d[top[y]]) {
            swap(x, y);
        }
    }  
    return (d[x] < d[y]) ? x : y;  
}  
void pushup(int k, int l, int r) {  
    if(l < r) {
        val[k] = min(val[k<<1], val[k<<1|1]); 
    } else { 
        val[k] = INF;  
    }
    if(tag[k]) {
        val[k] = min(val[k], min(d[dfm[l]] * lk[k], d[dfm[r]] * lk[k]) + lb[k]);
    }
}  
void build(int k, int l, int r) {  
    val[k] = INF;  
    if(l < r) {  
        int mid = (l + r) / 2; 
        build(k<<1, l, mid); 
        build(k<<1|1, mid + 1, r);  
    }  
}  
void merge(int k, int l, int r, int u, ll v) {  
    if(!tag[k]) { 
        tag[k] = 1; 
        lk[k] = u; 
        lb[k] = v; 
    } else {  
        ll x1 = d[dfm[l]] * u + v;
        ll y1 = d[dfm[r]] * u + v;
        ll x2 = d[dfm[l]] * lk[k] + lb[k];
        ll y2 = d[dfm[r]] * lk[k] + lb[k];  
        int mid = (l + r) / 2;  
        if(x1 <= x2 && y1 <= y2) {  
            lk[k] = u; 
            lb[k] = v;  
        } else if(x1 >= x2 && y1 >= y2) {
            return;
        } else if(u < lk[k]) {  
            ll tmp = (v - lb[k]) / (lk[k] - u) + 1;  
            if(tmp <= d[dfm[mid]]) {  
                swap(u, lk[k]); 
                swap(v, lb[k]);  
                merge(k<<1, l, mid, u, v);  
            } else {
                merge(k<<1|1, mid + 1, r, u, v);  
            }
        } else {  
            ll tmp = (lb[k] - v - 1) / (u - lk[k]);  
            if(tmp > d[dfm[mid]]) {  
                swap(u, lk[k]); 
                swap(v, lb[k]);  
                merge(k<<1|1, mid + 1, r, u, v);  
            } else {
                merge(k<<1, l, mid, u, v);
            }
        }  
    }  
    pushup(k, l, r);  
}  
void insert(int k, int l, int r, int x, int y, int u, ll v){  
    if (l == x && r == y) { 
        merge(k, l, r, u, v); 
        return; 
    }  
    int mid = (l + r) / 2;  
    if(y <= mid) {
        insert(k<<1, l, mid, x, y, u, v); 
    } else if(x > mid) {
        insert(k<<1|1, mid + 1, r, x, y, u, v); 
    } else {  
        insert(k<<1, l, mid, x, mid, u, v); 
        insert(k<<1|1, mid + 1, r, mid + 1, y, u, v);  
    }  
    pushup(k, l, r);  
}  
void query(int k, int l, int r, int x, int y) {  
    if(l == x && r == y) { 
        ans = min(ans, val[k]); 
        return; 
    }  
    if(tag[k]) {
        ans = min(ans, min(d[dfm[x]] * lk[k], d[dfm[y]] * lk[k]) + lb[k]);
    }  
    int mid = (l + r) / 2;  
    if(y <= mid) {
        query(k<<1, l, mid, x, y);
    } else if(x > mid) {
        query(k<<1|1, mid + 1, r, x, y); 
    } else {  
        query(k<<1, l, mid, x, mid); 
        query(k<<1|1, mid + 1, r, mid + 1, y);  
    }  
}  
int main() {  
    n = read(); m = read(); 
    int x, y, z;  
    for (int i = 1; i < n; i++) {  
        x = read(); y = read(); z = read();  
        add(x, y, z); add(y, x, z);  
    }  
    dfs(1); dfs2(1, 1); 
    build(1, 1, n); 
    int k, u, v; ll tmp;  
    while(m--) {  
        k = read();  
        if(k == 1) {  
            x = read(); y = read(); u = read(); v = read(); z = lca(x, y);  
            tmp = d[x] * u + v;  
            for(; top[x] != top[z]; x = fa[top[x]]) {
                insert(1, 1, n, dfn[top[x]], dfn[x], -u, tmp);
            }  
            insert(1, 1, n, dfn[z], dfn[x], -u, tmp);  
            tmp -= (d[z] << 1) * u;  
            for(; top[y] != top[z]; y = fa[top[y]]) {
                insert(1, 1, n, dfn[top[y]], dfn[y], u, tmp);
            }  
            insert(1, 1, n, dfn[z], dfn[y], u, tmp);  
        } else {  
            x = read(); y = read(); ans = INF;  
            for(; top[x] != top[y]; x = fa[top[x]]) {  
                if(d[top[x]] < d[top[y]]) {
                    swap(x, y);
                }
                query(1, 1, n, dfn[top[x]], dfn[x]);  
            }  
            if(d[x] > d[y]) {
                swap(x, y); 
            }  
            query(1, 1, n, dfn[x], dfn[y]);
            printf("%lld\n", ans);  
        }  
    }  
    return 0;  
}