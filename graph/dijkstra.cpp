class dijkstra{ // matrix form is similar
public:
    vi(ll)d, p;
    vi(bool)vis;
    ll s;
    dijkstra(ll S){
        s=S;
    }
    void dijkstraDense(const vi(vi(pi))&g) { // for max edges; O(v^2)
        ll n = g.size();
        d.assign(n, LLONG_MAX), p.assign(n, -1), vis.assign(n, false);
        d[s] = 0;
        for (ll i = 0; i < n; i++) {
            ll v = -1;
            for (ll j = 0; j < n; j++) {
                if (!vis[j] && (v == -1 || d[j] < d[v])){
                    v = j;
                }
            }
            if (v==-1 || d[v] == LLONG_MAX){
                break;
            }
            vis[v] = true;
            for (const auto&[to, w] : g[v]) {
                if (d[v] + w < d[to]) {
                    d[to] = d[v] + w;
                    p[to] = v;
                }
            }
        }
    }
    void dijkstraSparse(const vi(vi(pi))&g) { // for min edges; O(elogn)
        ll n = g.size();
        d.assign(n, LLONG_MAX), p.assign(n, -1);
        d[s] = 0;
        priority_queue<pi, vector<pi>, greater<pi>> q;
        q.push({0, s});
        while (!q.empty()) {
            const auto&[dist, v] = q.top();
            q.pop();
            if (dist != d[v]){
                continue;
            }
            for (const auto&[to, w] : g[v]) {
                if (d[v] + w < d[to]) {
                    d[to] = d[v] + w;
                    p[to] = v;
                    q.push({d[to], to});
                }
            }
        }
    }
    //  restore path using array p
};