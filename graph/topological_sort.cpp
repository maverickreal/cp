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