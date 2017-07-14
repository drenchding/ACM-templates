//loj101
//Dinic最大流
//第一行四个数n, m, s, t, 分别表示点、边、源、汇
//接下来m行, 每行三个数u, v, c, 表示u->v一条流量为c的边
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 1000005;
const int MAXM = 8000006;
const int INF = 0x7fffffff;
struct edge {
    int to, cap, rev;
};
struct Dinic {
    int n, m, t;
    edge w[MAXM], e[MAXM];
    int fr[MAXM], num[MAXN], cur[MAXN], first[MAXN], q[MAXN], dist[MAXN];
    void init(int n) {
        this->n = n;
        m = 0;
    }
    void addedge(int from, int to, int cap) {
        w[++m] = (edge){to, cap};
        num[from]++, fr[m] = from;
        w[++m] = (edge){from, 0};
        num[to]++, fr[m]=to;
    }
    void prepare(){
        first[1] = 1;
        for(int i = 2; i <= n; i++) {
            first[i] = first[i - 1] + num[i - 1];
        }
        for(int i = 1; i < n; i++) {
            num[i] = first[i + 1] - 1;
        }
        num[n] = m;
        for(int i = 1; i <= m; i++) {
            e[first[fr[i]] + (cur[fr[i]]++)] = w[i];
            if(!(i % 2)) {
                e[first[fr[i]] + cur[fr[i]] - 1].rev = first[w[i].to] + cur[w[i].to] - 1;
                e[first[w[i].to] + cur[w[i].to] - 1].rev = first[fr[i]] + cur[fr[i]] - 1;
            }
        }
    }
    bool bfs(int s) {
        int l = 1, r = 1;
        q[1] = s;
        memset(dist, -1, (n + 1) * 4);
        dist[s] = 0;
        while(l <= r) {
            int u = q[l++];
            for(int i = first[u]; i <= num[u]; i++) {
                int v = e[i].to;
                if((dist[v] != -1) || (!e[i].cap)) {
                    continue;
                }
                dist[v] = dist[u] + 1;
                if(v == t) {
                    return true;
                }
                q[++r] = v;
            }
        }
        return dist[t] != -1;
    }
    int dfs(int u, int flow) {
        if(u == t) {
            return flow;
        }
        for(int & i = cur[u]; i <= num[u]; i++) {
            int v = e[i].to;
            if(!e[i].cap || dist[v] != dist[u] + 1) {
                continue;
            }
            int t = dfs(v, min(flow, e[i].cap));
            if(t) {
                e[i].cap -= t;
                e[e[i].rev].cap += t;
                return t;
            }
        }
        return 0;
    }
    ll dinic(int s, int t) {
    	prepare();
        ll ans = 0;
        this->t = t;
        while(bfs(s)) {
            int flow;
            for(int i = 1; i <= n; i++) {
                cur[i] = first[i];
            }
            while(flow = dfs(s, INF)) {
                ans += 1LL * flow;
            }
        }
        return ans;
    }
}fw, *Flow;
int n, m, s, t;
int main() {
	Flow = &fw;
	scanf("%d %d %d %d", &n, &m, &s, &t);
    Flow->init(n);
    for(int i = 1; i <= m; i++) {
    	int u, v, c;
    	scanf("%d %d %d", &u, &v, &c);
    	Flow->addedge(u, v, c);
    }
    printf("%lld\n",Flow->dinic(s, t));
    return 0;
}