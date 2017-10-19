#include <cstdio>
#include <bitset>
#include <vector>
#include <cstring>
#include <iostream>
 
using namespace std;
 
const int MAXN = 30005;
 
int vis[MAXN];
 
bitset<MAXN> reach[MAXN];
 
vector<int> G[MAXN];
 
void dfs(int cur) {
  for(int i = 0; i < G[cur].size(); i++) {
    int nx = G[cur][i];
    if(!vis[nx]) {
      vis[nx] = 1;
      dfs(nx);
    }
    reach[cur][nx] = 1;
    reach[cur] |= reach[nx];
  }
}

void addEdge(int u, int v) {
  G[u].push_back(v);
  reach[u][v] = 1;
}
