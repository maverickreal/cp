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