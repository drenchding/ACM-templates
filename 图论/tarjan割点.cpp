#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
const int MAXN = 100005;
vector<int> G[MAXN];
bool vis[MAXN], flag[MAXN];
int cnt, fa[MAXN], dfn[MAXN], low[MAXN];
void tarjan(int cur) {
    vis[cur] = true;
    dfn[cur] = low[cur] = ++cnt;
    int children = 0;
    for(int i = 0; i < G[cur].size(); i++) {
        int nx = G[cur][i];
        if(!vis[nx]) {
            children++;
            fa[nx] = cur;
            tarjan(nx);
            low[cur] = min(low[cur], low[nx]);
            if(!fa[cur] && children > 1) {
                flag[cur] = true;
            } else if(fa[cur] && low[nx] >= dfn[cur]) {
                flag[cur] = true;
            }
        } else {
            low[cur] = min(low[cur], dfn[nx]);
        }
    }
}