ll modBinExp(ll x, ll y, ll m){
    ll res = 1;
    x%=m;
    if (!x){
        return 0;  
    }
    while (y > 0){
        if (y & 1){
            res = (res*x) % m;
        }
        y>>=1;
        x = (x*x) % m;
    }
    return res;
}

vi(ll) extendedEucledian(ll a, ll b) {
    if(!b){
        return {1, 0, a};
    }
    vi(ll)xyg = extendedEucledian(b, a%b);
    ll x = xyg[1], y = xyg[0]-xyg[1]*(a/b);
    return {x, y, xyg[2]};
}