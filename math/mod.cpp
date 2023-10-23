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

vi(ll) extendedEucledianGcd(ll a, ll b) {
   if (!b){
       return {a, 1, 0};
   }
   vi(ll) gxy = extendedEucledianGcd(b, a % b);
   ll x = gxy[2], y = gxy[1] - gxy[2] * (a / b);
   return {gcd, x, y};
}