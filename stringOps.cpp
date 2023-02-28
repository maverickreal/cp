string manacher(const string&str) { // {T.C: O(n) | S.P.:  O(1)} -> get L.P.S., all palindromes, occurrences, sizes, etc...
    ll n=str.size(), m=2*n+1;
    string sDash(m, '#');
    for(ll i=0;i<n;++i){
        sDash[2*i+1]=str[i];
    }
    vi(ll)cp(m);
    ll lpc=0, lps=0, rpc=0, rpr=0;
    for(ll i=0;i<m;++i){
        if(i<rpr){
            cp[i]=min(rpr-i, cp[2*rpc-i]);
        }
        ll l=i-cp[i]-1, r=i+cp[i]+1;
        while(l>-1 && r<m && sDash[l]==sDash[r]){
            --l, ++r, ++cp[i];
        }
        if(cp[i]>lps){
            lps=cp[i], lpc=i;
        }
        if(i+cp[i]>rpr){
            rpr=cp[i]+i, rpc=i;
        }
    }
    string ans;
    for(ll i=lpc-lps;i<=lpc+lps;++i){
        if(sDash[i]!='#'){
            ans.pb(sDash[i]);
        }
    }
    return ans; // L.P.S.
}

/*
-> For computing hashes in mass/iteratively.
-> Used in Rabin-Karp to find the occurances of a string in another.
*/

class rollingHash {
public:
    ll n, m, base;
    vi(ll) pow, hash;
    rollingHash(const string &s, ll B=97, ll M=(1LL<<61)-1){
        n=s.size(), m=M, base=B, pow.resize(n), hash.resize(n);
        pow[0] = 1, hash[0]=s[0];
        for (ll i = 1; i < n; i++) {
            hash[i] = (hash[i-1] * base + s[i]) % mod;
            pow[i] = (pow[i-1] * base) % mod;
        }
    }
    ll get(ll l, ll r){
        if(!l){
            return hash[r];
        }
        return (hash[r] - (hash[l-1] * pow[r - l + 1] % mod) + mod) % mod;
    }
};