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
    vi(ll) x = {1, 0, a}, y = {0, 1, b};
	while (y[2] > 0) {
		ll k = x[2] / y[2];
		for (ll i = 0; i < 3; ++i){
            x[i] -= k * y[i];
        }
		swap(x, y);
	}
	return x;
}