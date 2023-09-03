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