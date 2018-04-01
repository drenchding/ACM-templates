#include <cstdio>
#include <cstring>
#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef long long ll;
int n, m;
namespace Dijkstra {
    using namespace __gnu_pbds;
    typedef pair<ll, int> pa;
    typedef __gnu_pbds::priority_queue<pa, greater<pa>, pairing_heap_tag> heap;
    const ll INF = 9000000000000000000LL;
    const int MAXN = 1000005;
    const int MAXM = 10000005;
    int cnt, last[MAXN];
    heap::point_iterator id[MAXN];
    ll dis[MAXN];
    struct data {
        int to, next, v;
    }e[MAXM];
    void addedge(int u, int v, int w) {
        e[++cnt].to = v; e[cnt].next = last[u]; last[u] = cnt; e[cnt].v = w;
    }
    void dijkstra(int s) {
        heap Q;
        for(int i = 1; i <= n; i++) {
            dis[i] = INF;
        }
        dis[s] = 0; id[s] = Q.push(make_pair(0, s));
        while(!Q.empty()) {
            int now = Q.top().second; Q.pop();
            for(int i = last[now]; i; i = e[i].next) {
                if(e[i].v + dis[now] < dis[e[i].to]) {
                    dis[e[i].to] = e[i].v + dis[now];
                    if(id[e[i].to] != 0) {
                        Q.modify(id[e[i].to], make_pair(dis[e[i].to], e[i].to));
                    } else {
                        id[e[i].to] = Q.push(make_pair(dis[e[i].to], e[i].to));
                    }
                }
            }
        }
    }
}