// 有一天一位灵魂画师画了一张图，现在要你找出欧拉回路，即在图中找一个环使得每条边都在环上出现恰好一次。

#include <stack>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

const int MAXN = 100010;

using namespace std;

struct Edge {
  int to, val, ban;
  Edge *next;
};
Edge *E[MAXN], Pr[MAXN<<3];
int cnt;
int in[MAXN], out[MAXN];

void addedge(int u, int v, int val) {
  Pr[++cnt].to = v; Pr[cnt].val = val; Pr[cnt].next = E[u]; E[u] = &Pr[cnt];
  in[v]++; out[u]++;
}

bool vi[MAXN<<3];
stack<int> s;

void dfs(int u){
  for(Edge *P = E[u]; P; P = E[u]) {
    while(P && vi[abs(P->val)]) P = P->next;
    if(!P)return;
    vi[abs(P->val)] = 1;
    E[u] = P->next;
    dfs(P->to); s.push(P->val);
  }
}

int n, m, TP;

int main(){
  scanf("%d", &TP);
  scanf("%d %d", &n, &m);
  for(int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    addedge(u, v, i);
    if(TP == 1) addedge(v, u, -i);
  }
  for(int i = 1; i <= n; i++)
    if(in[i] != out[i] || (TP == 1 && in[i] % 2)) {
      puts("NO"); return 0;
    }
  dfs(Pr[cnt].to);
  for(int i = 1; i <= m; i++) if(!vi[i]) {
    puts("NO"); return 0;
  }
  puts("YES");
  while(!s.empty()) printf("%d ", s.top()), s.pop();
  return 0;
}