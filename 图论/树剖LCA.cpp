#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
const int MAXN = 100005;
vector<int> G[MAXN];
int cnt;
int fa[MAXN], size[MAXN], deep[MAXN];
int son[MAXN], dfn[MAXN], top[MAXN];
void dfs1(int cur, int father, int dep) {
    fa[cur] = father;
    deep[cur] = dep;
    size[cur] = 1;
    son[cur] = 0;
    for(int i = 0; i < G[cur].size(); i++) {
        int nx = G[cur][i];
        if(nx == fa[cur]) continue;
        dfs1(nx, cur, dep + 1);
        size[cur] += size[nx];
        if(size[son[cur]] < size[nx]) {
            son[cur] = nx;
        }
    }
}
void dfs2(int cur, int tp) {
    top[cur] = tp;
    dfn[cur] = ++cnt;
    if(!son[cur]) return;
    dfs2(son[cur], tp);
    for(int i = 0; i < G[cur].size(); i++) {
        int nx = G[cur][i];
        if(nx == fa[cur] || nx == son[cur]) {
            continue;
        }
        dfs2(nx, nx);
    }
}
int lca(int x, int y) {
    int t1 = top[x], t2 = top[y];
    while(t1 != t2) {
        if(deep[t1] < deep[t2]) {
            swap(t1, t2);
            swap(x, y);
        }
        x = fa[t1]; t1 = top[x];
    }
    return deep[x] < deep[y] ? x : y;
}