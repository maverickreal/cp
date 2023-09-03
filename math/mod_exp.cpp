ll modExp(ll x, ll y, ll m){
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