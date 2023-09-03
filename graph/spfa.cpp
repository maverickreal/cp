bool spfa(const vi(vi(pi))&g, vi(ll)&d, ll s) { // optimized bellman ford
    ll n = g.size();
    d.assign(n, LLONG_MAX);
    vi(ll)cnt(n, 0);
    vi(bool)vis(n);
    list<ll>q={s};
    d[s] = 0;
    vis[s] = true;
    while (!q.empty()) {
        ll v = q.front();
        q.pop_front();
        vis[v] = false;
        for (const auto&[u, w] : g[v]) {
            if (d[v] + w < d[u]) {
                d[u] = d[v] + w;
                if (!vis[u]) {
                    q.push_back(u);
                    vis[u] = true;
                    if (++cnt[u] > n){
                        return false; // negative cycle
                    }
                }
            }
        }
    }
    return true;
}