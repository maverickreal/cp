class tarjan{ // find articulation points and bridges in O(e+v) time
public:
    ll n, time;
    vi(bool)vis;
    vi(ll)disc, low, pts;
    vi(vi(ll))bridges;
    void dfsPoints(const vi(vi(ll))&g, ll nd, ll par) {
        vis[nd] = 1;
        disc[nd] = low[nd] = time++;
        ll children=0;
        for (ll child : g[nd]) {
            if (child == par){
                continue;
            }
            if (vis[child]) {
                low[nd] = min(low[nd], disc[child]);
            }
            else {
                dfsPoints(g, child, nd);
                low[nd] = min(low[nd], low[child]);
                if (low[child] >= disc[nd] && par!=-1){
                    pts.pb(nd);
                }
                ++children;
            }
        }
        if(par == -1 && children > 1){
            pts.pb(nd);
        }
    }
    void tarjanPoints(const vi(vi(ll))&g){
        time = 0, n=g.size();
        vis.assign(n, 0), disc.assign(n, -1), low.assign(n, -1);
        for (ll i = 0; i < n; ++i) {
            if (!vis[i]){
                dfsPoints(g, i, -1);
            }
        }
    }
    void dfsBridges(const vi(vi(ll))&g, ll nd, ll par) {
        vis[nd] = 1;
        disc[nd] = low[nd] = time++;
        for (ll child : g[nd]) {
            if (child == par){
                continue;
            }
            if (vis[child]) {
                low[nd] = min(low[nd], disc[child]);
            }
            else {
                dfsBridges(g, child, nd);
                low[nd] = min(low[nd], low[child]);
                if (low[child] > disc[nd]){
                    bridges.pb({nd, child});
                }
            }
        }
    }
    void tarjanBridges(const vi(vi(ll))&g) {
        time = 0, n=g.size();
        vis.assign(n, 0), disc.assign(n, -1), low.assign(n, -1);
        for (ll i = 0; i < n; ++i) {
            if (!vis[i]){
                dfsBridges(g, i, -1);
            }
        }
    }
};