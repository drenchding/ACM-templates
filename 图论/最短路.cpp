void spfa(int sta) {
    memset(dis, 127, sizeof(dis));
    dis[sta] = 0; 
    queue<int>Q; Q.push(sta);
    while(!Q.empty()) {
        int cur = Q.front(); Q.pop();
        for(int i = 0; i < G[cur].size(); i++) {
            int nx = G[cur][i].to;
            int newd = G[cur][i].dis + dis[cur];
            if(newd < dis[nx]) {
                dis[nx] = newd;
                pre[nx] = cur;
                Q.push(nx);
            }
        }
    }
}
void dijkstra(int sta) {
    #define pr pair<int, int>
    priority_queue<pr, vector<pr>, greater<pr> >Q;
    memset(dis, 127, sizeof(dis));
    dis[sta] = 0;
    Q.push(make_pair(0, sta));
    while(!Q.empty()) {
        int cur = Q.top().second; Q.pop();
        if(vis[cur]) continue;
        vis[cur] = 1;
        for(int i = 0; i < G[cur].size(); i++) {
            int nx = G[cur][i].to;
            if(dis[cur] + G[cur][i].dis < dis[nx]) {
                dis[nx] = dis[cur] + G[cur][i].dis;
                pre[nx] = cur;
                Q.push(make_pair(dis[nx], nx));
            }
        }
    }
}