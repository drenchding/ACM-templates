//bzoj4695
//segment beats
//第一行一个n, 表示序列长度
//接下来一行n个数, 表示序列
//接下来一个m, 表示操作数
//接下来m个操作:
//1 l r x [l,r]加x
//2 l r x [l,r]对x取max
//3 l r x [l,r]对x取min
//4 l r 询问[l,r]和
//5 l r 询问[l,r]最大值
//6 l r 询问[l,r]最小值
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int INF = 1<<29;
const int MAXN = 2000005;
char c; bool flag;
int Data[MAXN];
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
struct Node {
    int maxtime, fmax, smax, mintime, fmin, smin, maxtag, mintag, addtag; ll sum;
    Node(){}
    Node(int data): maxtag(-INF), fmax(data), smax(-INF), maxtime(1), mintag(-INF), fmin(data), smin(INF), mintime(1), addtag(0), sum(data) {}
}T[MAXN];
void chkmin(int &a, int b) {
    a < b ? a : a = b; 
}
void chkmax(int &a, int b) {
    a > b ? a : a = b;
}
void MinTag(int cur, int tag, int L, int R) {
    if(T[cur].fmax <= tag) {
        return;
    }
    T[cur].sum -= 1LL * (T[cur].fmax - tag) * T[cur].maxtime;
    T[cur].fmax = tag;
    if(R - L + 1 == T[cur].maxtime) {
        chkmin(T[cur].fmin, tag);
    } else {
        chkmin(T[cur].smin, tag);
    }
    T[cur].mintag = tag;
    if(T[cur].maxtag ^ -INF) {
        if(T[cur].maxtag > T[cur].mintag){
            T[cur].maxtag = T[cur].mintag;
        }
    }
}
void MaxTag(int cur, int tag, int L, int R) {
    if(T[cur].fmin >= tag) {
        return;
    }
    T[cur].sum -= 1LL * (T[cur].fmin - tag) * T[cur].mintime;
    T[cur].fmin = tag;
    if(R - L + 1 == T[cur].maxtime) {
        chkmax(T[cur].fmax, tag);
    } else {
        chkmax(T[cur].smax, tag);
    }
    T[cur].maxtag = tag;
    if(T[cur].mintag ^ -INF) {
        if(T[cur].maxtag > T[cur].mintag) {
            T[cur].mintag = T[cur].maxtag;
        }
    }
}
void AddTag(int cur, int tag, int L, int R) {
    T[cur].sum += 1LL * tag * (R - L + 1);
    T[cur].fmax += tag;
    if(R - L + 1 != T[cur].maxtime) {
        T[cur].smax += tag;
    }
    T[cur].fmin += tag;
    if(R - L + 1 != T[cur].maxtime) {
        T[cur].smin += tag;
    }
    T[cur].addtag += tag;
    if(T[cur].maxtag != -INF) {
        T[cur].maxtag += tag;
    }
    if(T[cur].mintag != -INF) {
        T[cur].mintag += tag;
    }
}
void Push(int cur, int L, int R) {
    int mid = (L + R) / 2;
    if(T[cur].addtag) {
        AddTag(cur<<1, T[cur].addtag, L, mid);
        AddTag(cur<<1|1, T[cur].addtag, mid + 1, R);
        T[cur].addtag = 0;
    }
    if(T[cur].maxtag ^ -INF) {
        MaxTag(cur<<1, T[cur].maxtag, L, mid);
        MaxTag(cur<<1|1, T[cur].maxtag, mid + 1, R);
        T[cur].maxtag = -INF;
    }
    if(T[cur].mintag ^ -INF) {
        MinTag(cur<<1, T[cur].mintag, L, mid);
        MinTag(cur<<1|1, T[cur].mintag, mid + 1, R);
        T[cur].mintag = -INF;
    }
}
void Up(int cur) {
    T[cur].maxtime = T[cur].mintime = 0;
    int lc = cur<<1, rc = lc|1;
    T[cur].sum = T[lc].sum + T[rc].sum;
    if(T[lc].fmax == T[rc].fmax) {
        T[cur].fmax = T[rc].fmax;
        T[cur].maxtime = T[lc].maxtime + T[rc].maxtime;
        T[cur].smax = max(T[lc].smax, T[rc].smax);
    } else if(T[lc].fmax > T[rc].fmax) {
        T[cur].fmax = T[lc].fmax;
        T[cur].maxtime = T[lc].maxtime;
        T[cur].smax = max(T[lc].smax, T[rc].fmax);
    } else {
        T[cur].fmax = T[rc].fmax;
        T[cur].maxtime = T[rc].maxtime;
        T[cur].smax = max(T[rc].smax, T[lc].fmax);
    }
    if(T[lc].fmin == T[rc].fmin) {
        T[cur].fmin = T[rc].fmin;
        T[cur].mintime = T[lc].mintime + T[rc].mintime;
        T[cur].smin = min(T[lc].smin, T[rc].smin);
    } else if(T[lc].fmin < T[rc].fmin) {
        T[cur].fmin = T[lc].fmin;
        T[cur].mintime = T[lc].mintime;
        T[cur].smin = min(T[lc].smin, T[rc].fmin);
    } else {
        T[cur].fmin = T[rc].fmin;
        T[cur].mintime = T[rc].mintime;
        T[cur].smin = min(T[rc].smin, T[lc].fmin);
    }
}
void MIN(int cur, int l, int r, int p, int L,int R) {
    if(T[cur].fmax <= p) {
        return;
    }
    if(L >= l && R <= r && T[cur].fmax > p && T[cur].smax < p) {
        return MinTag(cur, p, L, R);
    }
    Push(cur, L, R);
    int Mid = (L + R) / 2;
    if(l <= Mid) {
        MIN(cur<<1, l, r, p, L, Mid);
    }
    if(r > Mid) {
        MIN(cur<<1|1, l, r, p, Mid + 1, R);
    }
    Up(cur);
}
void MAX(int cur, int l, int r, int p, int L, int R) {
    if(T[cur].fmin >= p) {
        return;
    }
    if(L >= l && R <= r && T[cur].fmin < p && T[cur].smin > p) {
        return MaxTag(cur, p, L, R);
    }
    Push(cur, L, R);
    int Mid = (L + R) / 2;
    if(l <= Mid) {
        MAX(cur<<1, l, r, p, L, Mid);
    }
    if(r > Mid) {
        MAX(cur<<1|1, l, r, p, Mid + 1, R);
    }
    Up(cur);
}
void Add(int cur, int l, int r, int tag, int L, int R) {
    if(L >= l && R <= r) {
        return AddTag(cur, tag, L, R);
    }
    Push(cur, L, R);
    int mid = (L + R) / 2;
    if(mid >= l) {
        Add(cur<<1, l, r, tag, L, mid);
    }
    if(mid < r) {
        Add(cur<<1|1, l, r, tag, mid + 1, R);
    }
    Up(cur);
}
ll Sum(int cur, int l, int r, int L, int R) {
    if(L >= l && R <= r) {
        return T[cur].sum;
    }
    Push(cur, L, R);
    int mid = (L + R) / 2;
    ll res = 0;
    if(mid >= l) {
        res += Sum(cur<<1, l, r, L, mid);
    }
    if(mid < r) {
        res += Sum(cur<<1|1, l, r, mid + 1, R);
    }
    return res;
}
int Querymin(int cur, int l, int r, int L, int R) {
    if(L >= l && R <= r) {
        return T[cur].fmin;
    }
    Push(cur, L, R);
    int mid = (L + R) / 2;
    int res = INF;
    if(mid >= l) {
        chkmin(res, Querymin(cur<<1, l, r, L, mid));
    }
    if(mid < r) {
        chkmin(res, Querymin(cur<<1|1, l, r, mid + 1, R));
    }
    return res;
}
int Querymax(int cur, int l, int r, int L, int R) {
    if(L >= l && R <= r) {
        return T[cur].fmax;
    }
    int mid = (L + R) / 2;
    Push(cur, L, R);
    int res = -INF;
    if(mid >= l) {
        chkmax(res, Querymax(cur<<1, l, r, L, mid));
    }
    if(mid < r) {
        chkmax(res, Querymax(cur<<1|1, l, r, mid + 1, R));
    }
    return res;
}
void Build(int cur, int l, int r) {
    T[cur] = Node(Data[l]);
    if(l ^ r) {
        int mid = (l + r) / 2;
        Build(cur<<1, l, mid);
        Build(cur<<1|1, mid + 1, r);
        Up(cur); 
    }
}
void out(ll a) {
    if(a < 0) {
        putchar('-');
        a = -a;
    }
    if(a > 9) {
        out(a / 10);
    }
    putchar('0' + a % 10);
}
int main() {
    int n = read();
    for(int i = 1; i <= n; i++) {
        Data[i] = read();
    }
    Build(1, 1, n);
    int m = read();
    while(m--) {
        int opt = read();
        int l = read(), r = read(), t;
        if(opt == 1) {
            t = read();
            Add(1, l, r, t, 1, n);
        } else if(opt == 2) {
            t = read();
            MAX(1, l, r, t, 1, n);
        } else if(opt == 3) {
            t = read();
            MIN(1, l, r, t, 1, n);
        } else if(opt == 4) {
            out(Sum(1, l, r, 1, n));
            putchar('\n');
        } else if(opt == 5) {
            out(Querymax(1, l, r, 1, n));
            putchar('\n');
        } else {
            out(Querymin(1, l, r, 1, n));
            putchar('\n');
        }   
    }
    return 0;
}