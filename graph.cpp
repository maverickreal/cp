void topologicalSort(const vi(vi(ll))&g, vi(ll)&v){ // matrix form similar
    ll n=g.size();
    vi(ll)ind(n);
    for(auto it:g){
        for(auto nd:it){
            ++ind[nd];
        }
    }
    list<ll>l;
    for(ll i=0;i<n;++i){
        if(!ind[i]){
            l.pb(i);
        }
    }
    while(!l.empty()){
        ll nd=l.front();
        l.pop_front();
        v.pb(nd);
        for(ll child:g[nd]){
            if(--ind[child]==0){
                l.pb(child);
            }
        }
    }
    if(v.size()!=n){ // graph is cyclic
        v.clear();
    }
}

void floydWarshall(vi(vi(ll))&g){ // adjust for list form
    ll n=g.size();
    for(ll k=0;k<n;++k){
        for(ll i=0;i<n;++i){
            for(ll j=0;j<n;++j){
                if(g[i][k]<LLONG_MAX && g[k][j]<LLONG_MAX){
                    g[i][j]=min(g[i][j], g[i][k]+g[k][j]);
                }
            }
        }
    }
}

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

class dsu{
public:
    vi(ll)par, size;
    dsu(ll n){
        par.assign(n, 0), size.assign(n, 1);
        iota(begin(par), end(par), 0);
    }
    ll find(ll n){
        if(par[n]==n){
            return n;
        }
        return (par[n]=find(par[n]));
    }
    void merge(ll a, ll b){
        a=find(a), b=find(b);
        if(a==b){
            return;
        }
        if(size[a]<size[b]){
            a+=b, b=a-b, a-=b;
        }
        par[b]=a;
        size[a]+=size[b];
    }
};

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

ll primsAcc(const vi(ll)&val, const vi(bool)&inc){ // find and return the min valued vertex
    ll mn = LLONG_MAX, v=-1;
    for(ll i = 0; i < val.size(); ++i){
        if(!inc[i] && val[i] < mn){
            v = i, mn = val[i];
        }
    }
    return v;
}

bool primsMst(const vi(vi(ll))&g){ // find MST in a dense graph
    ll n=g.size();
    vi(ll)par(n, 0), val(n, LLONG_MAX);
    vi(bool)inc(n);
    par[0] = -1, val[0] = 0;
    for(ll i = 0; i < n-1; ++i){
        ll u = primsAcc(val, inc);
        if(u==-1){
            return false;
        }
        inc[u] = true;
        for(ll v = 0; v < n; ++v){
            if(g[u][v] && !inc[v] && g[u][v] < val[v]){
                val[v] = g[u][v], par[v] = u;
            }
        }
    }
    // figure out the MST using par array
    return true;
}

ll kruskal(const vi(vi(pi))&g){ // adjust for matrix form, or other requirements
    vi(vi(ll))e;
    ll n=g.size(), ans=0;
    for(ll nd=0; nd<n; ++nd){
        for(const pi&child:g[nd]){
            e.pb({nd, child.first, child.second});
        }
    }
    sort(begin(e), end(e), [](const vi(ll)&a, const vi(ll)&b){return (a[2]<b[2]);});
    dsu d(n);
    for(ll i=0;i<e.size();i++){
        if(d.find(e[i][0])!=d.find(e[i][1])){
            d.merge(e[i][0],e[i][1]);
            ans+=e[i][2];
        }
    }
    return ans;
}

bool dgHasEulerPath(const vi(vi(ll))&g) { // graph must be connected
   ll n=g.size(), u = 0, v = 0;
   vi(ll)in(n), out(n);
   for(ll i=0;i<n;i++) {
      for(ll j:g[i]) {
        ++in[j];
      }
      out[i]=g[i].size();
   }
   if(in==out){ // eulerian circuit found
    return 1;
   }
   for(ll i=0;i<n;i++) {
      if(in[i]==out[i]){
        continue;
      }
      if(in[i]==out[i]-1){
        ++u;
      }
      else if(out[i]==in[i]-1){
        ++v;
      }
   } // perform a postorder on u to trace the path
   return (u==1 && v==1);
}

bool undgHasEulerPath(const vi(vi(ll))&g) { // graph must be connected
   ll oddDeg=0;
   for(ll i=0;i<g.size();i++) {
      oddDeg+=g[i].size()&1;
   } // perform a postorder over either of the odd degree nodes to trace the path
   return (oddDeg==0 || oddDeg==2 /* eulerian circuit found */);
}