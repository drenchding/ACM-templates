#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 405;
const int MAXM = 15005;
struct ZKW {
	int first[MAXN], targ[MAXM<<1], nxt[MAXM<<1], flow[MAXM<<1], cost[MAXM<<1];
	int dist[MAXN], s, t, inf, ans, cnte;
	bool inq[MAXN], vis[MAXN];
	ZKW(): ans(0), cnte(2) { }
	void AddEdge(int u, int v, int l, int c) {
		targ[cnte] = v; flow[cnte] = l; cost[cnte] = c; nxt[cnte] = first[u]; first[u] = cnte++;
		targ[cnte] = u; flow[cnte] = 0; cost[cnte] = -c; nxt[cnte] = first[v]; first[v] = cnte++;
	}
	bool SPFA() {
		memset(dist, 127, sizeof(dist));
		memset(&inf, 127, sizeof(int));
		memset(inq, 0, sizeof(inq));
		queue<int> Q;
		dist[t] = 0; inq[t] = 1; Q.push(t);
		while(!Q.empty()) {
			int x = Q.front(); Q.pop(); inq[x] = 0;
			for(int i = first[x]; i; i = nxt[i]) {
				if(flow[i ^ 1] && dist[targ[i]] > dist[x] - cost[i]) {
					dist[targ[i]] = dist[x] - cost[i];
					if(!inq[targ[i]]) {
						Q.push(targ[i]);
						inq[targ[i]] = 1;
					}
				}
			}
		}
		return dist[s] ^ inf;
	}
	int DFS(int x, int maxflow) {
		if(x == t || !maxflow) {
			ans += dist[s] * maxflow;
			return maxflow;
		}
		if(vis[x]) return 0;
		vis[x] = 1;
		int ret = 0, f;
		for(int i = first[x]; i && maxflow; i = nxt[i]) {
			if(dist[targ[i]] == dist[x] - cost[i]) {
				if(f = DFS(targ[i], min(maxflow, flow[i]))) {
					ret += f;
					flow[i] -= f;
					flow[i ^ 1] += f;
					maxflow -= f;
				}
			}
		}
		vis[x] = 0;
		return ret;
	}
	int solve(int source, int tank) {
		s = source; t = tank;
		int Flow = 0;
		while(SPFA()) Flow += DFS(s,2147483647);
		return Flow;
	}
}zkw;
int main() {
	int n, m; scanf("%d %d", &n, &m);
	while(m--) {
		int s, t, c, w;
		scanf("%d %d %d %d", &s, &t, &c, &w);
		zkw.AddEdge(s, t, c, w);
	}
	int ret = zkw.solve(1, n);
	printf("%d %d\n", ret, zkw.ans);
	return 0;
}