#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

namespace Dis {
    const int MAXN = 500005;
    int dis[MAXN], vis[MAXN], pre[MAXN];
    typedef pair<int, int> PII;
    vector<PII> G[MAXN];
    void addEdge(int x, int y, int z) {
        G[x].push_back(make_pair(y, z));
    }
    void dijkstra(int s) {
        priority_queue<PII, vector<PII>, greater<PII> > Q;
        memset(dis, 127, sizeof(dis));
        dis[s] = 0;
        Q.push(make_pair(0, s));
        while(!Q.empty()) {
            int cur = Q.top().second; Q.pop();
            if(!vis[cur]) {
                vis[cur] = 1;
                for(int i = 0; i < G[cur].size(); i++) {
                    int nx = G[cur][i].first;
                    int d = G[cur][i].second;
                    if(dis[cur] + d < dis[nx]) {
                        dis[nx] = dis[cur] + d;
                        pre[nx] = cur;
                        Q.push(make_pair(dis[nx], nx));
                    }
                }
            }
        }
    }
}