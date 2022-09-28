#include "iostream"
#include "vector"
#include "list"
#include "limits.h"
#include "stack"
#include "unordered_map"
#include "unordered_set"
#include "set"
#include "map"
#include "math.h"
#include "algorithm"
#include "queue"
#include "functional"
#include "numeric"
#include "iomanip"
#include "bitset"

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;
#define vi(x) vector<x>
#define pb push_back
const ll mod = 1e9 + 7;
const char nl = '\n';

bitset<0> primes(0);

void setPrimes();

bool isPrime(ll n);

vi(vi(ll)) getChildren(vi(ll)& v);

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(10);
    ll tc = 1;
    cin >> tc;
    while (tc--) {
    }
    return 0;
}

void setPrimes() {
    ll n = primes.size();
    primes[0] = primes[1] = 0;
    for (ll i = 2;i * i <= n;i++) {
        if (primes[i]) {
            for (ll j = i;j * i <= n;++j)
                primes[j * i] = 0;
        }
    }
}

bool isPrime(ll n) {
    if (n == 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

vi(ll) getFactors(ll& n) {
    if (n < 0)
        return {};
    if (n == 0)
        return { 0 };
    vi(ll) res { 1 };
    for (ll i = 2;i * i <= n;i++) {
        if (n % i == 0) {
            res.push_back(i);
            if ((n / i) != i)
                res.push_back(n / i);
        }
    }
    return res;
}

vi(vi(ll)) getChildren(vi(ll)& v) {
    ll n = v.size();
    vi(vi(ll)) res(n);
    for (ll i = 0;i < n;++i) {
        ll node = i + 1, par = v[i];
        if (par == -1)continue;
        res[par - 1].push_back(node);
    }
    return res;
}

class dsu{
public:
    vi(ll)par, size;
    dsu(n){
        par.assign(n, 0), size(n, 1);
        for(ll i=0;i<n;++i){
            par[i]=i;
        }
    }
    ll find(ll n){
        if(par[n]==n){
            return n;
        }
        ll p=find(par[n]);
        par[n]=p;
        return p;
    }
    void union(ll a, ll b){
        a=find(a), b=find(b);
        if(a==b){
            return;
        }
        if(size[a]<size[b]){
            a^=b, b^=a, a^=b;
        }
        par[b]=a;
        size[a]+=size[b];
    }
};