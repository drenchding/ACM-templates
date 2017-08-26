#include <stack>
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;
const int MAXN = 100005;
stack<int> S;
vector<int> G[MAXN];
int cnt, tot;
int dfn[MAXN], low[MAXN];
int belong[MAXN], num[MAXN];
bool vis[MAXN], instack[MAXN];
inline void chkmin(int &x, int y) {
    if(y < x) x = y;
}
void tarjan(int cur) {
    S.push(cur);
    dfn[cur] = low[cur] = ++cnt;
    vis[cur] = instack[cur] = true;
    for(int i = 0; i < G[cur].size(); i++) {
        int nx = G[cur][i];
        if(!vis[nx]) {
            tarjan(nx);
            chkmin(low[cur], low[nx]);
        } else if(instack[nx]) {
            chkmin(low[cur], dfn[nx]);
        }
    }
    if(dfn[cur] == low[cur]) {
        int tp; tot++;
        do {
            tp = S.top(); S.pop();
            instack[tp] = false;
            belong[tp] = tot;
            num[tot]++;
        } while(tp != cur);
    }
}