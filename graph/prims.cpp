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