vector<bool>primes;

void setPrimes(ll n) { // first adjust "primes" accordingly
    primes.assign(n, 1);
    primes[0] = primes[1] = 0;
    for (ll i = 2;i * i <= n;i++) {
        if (primes[i]) {
            for (ll j = i;j * i <= n;++j){
                primes[j * i] = 0;
            }
        }
    }
}

bool isPrime(ll n) {
    if (n == 2){
        return true;
    }
    if (n<2 || !(n&1)){
        return false;
    }
    for (ll i = 3; i * i <= n; i += 2){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

unordered_map<ll,ll> getPrimeFactors(ll n){
    unordered_map<ll,ll>ump;
    for (ll i = 2; i*i<=n; ++i){
        while (n % i == 0){
            ++ump[i];
            n/=i;
        }
    }
    if (n > 2){
        ++ump[n];
    }
    return ump;
}

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
