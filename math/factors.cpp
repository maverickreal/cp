unordered_set<ll> getFactors(ll n) {
    if (n < 0){
        return {};
    }
    if (n == 0){
        return { 0 };
    }
    unordered_set<ll> res={1, n};
    for (ll i = 2;i * i <= n;i++) {
        if (n % i == 0) {
            res.insert(i), res.insert(n / i);
        }
    }
    return res;
}