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

bitset<0> primes(0); // <x> size initialised with bits of (y) right to left

void setPrimes(); //  first gust the bitset primes accordingly

bool isPrime(ll n);

unordered_map<ll, ll> getPrimeFactors(ll n); // for queries, use setPrimes and isPrime efficiently

unordered_set<ll> getFactors(ll n);

vi(vi(ll)) getChildren(vi(ll)& v);

ll modExp(ll x, ll y, ll m);

ll stringHash(const string&s);

void topologicalSort(const vi(vi(ll))&g, vi(ll)&v);

void floydWarshall(vi(vi(ll))&g);

bool spfa(const vi(vi(pi))&g, vi(ll)&d, ll s);

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(10);
    ll tc = 1;
    //cin >> tc;
    while(tc--){
    }
    return 0;
}

void setPrimes() {
    ll n = primes.size();
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
    if (n<2) return false;
    if (n == 2) return true;
    if (!(n&1)) return false;
    for (ll i = 3; i * i <= n; i += 2){
        if (n % i == 0) return false;
    }
    return true;
}

unordered_map<ll,ll> getPrimeFactors(ll n){
    unordered_map<ll,ll>ump;
    if(n<2){
        return ump;
    }
    while (!(n&1)){
        ++ump[2];
        n>>=1;
    }
    for (ll i = 3; i*i<=n; i+=2){
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
    if (n < 0)
        return {};
    if (n == 0)
        return { 0 };
    unordered_set<ll> res={1, n};
    for (ll i = 2;i * i <= n;i++) {
        if (n % i == 0) {
            res.insert(i), res.insert(n / i);
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

ll stringHash(const string& s) { // alternatively construct and use std::hash<>
    ll p = 31, hashVal = 0, pPow = 1;
    for(char ch : s) {
        hashVal = (hashVal + (ch - 'a' + 1) * pPow) % mod;
        pPow = (pPow * p) % mod;
    }
    return hashVal;
}

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

void floydWarshall(vi(vi(ll))&g){ // gust for list form
    ll n=g.size();
    for(ll k=0;k<n;++k){
        for(ll i=0;i<n;++i){
            for(ll j=0;j<n;++j){
                if(g[i][k]<LLNG_MAX && g[k][j]<LLONG_MAX){
                    g[i][j]=min(g[i][j], g[i][k]+g[k][j]);
                }
            }
        }
    }
}

bool spfa(const vi(vi(pi))&g, vi(ll)&d, ll s) { // optimized bellman ford
    ll n = g.size();
    d.assign(n, LLONG_MAX);
    vi(ll)cnt(n, 0);
    vi(bool)vis(n);
    list<ll>q={s};
    d[s] = 0;
    vis[s] = true;
    while (!q.empty()) {
        ll v = q.front();
        q.pop_front();
        vis[v] = false;
        for (auto edge : g[v]) {
            ll u = edge.first, w = edge.second;
            if (d[v] + w < d[u]]) {
                d[u] = d[v] + w;
                if (!vis[u]) {
                    q.push_back(u);
                    vis[u] = true;
                    cnt[u]++;
                    if (cnt[to] > n){
                        return false; // negative cycle
                    }
                }
            }
        }
    }
    return true;
}

class dsu{
public:
    vi(ll)par, size;
    dsu(ll n){
        par.assign(n, 0), size.assign(n, 1);
        for(ll i=0;i<n;++i){
            par[i]=i;
        }
    }
    ll find(ll n){
        if(par[n]==n){
            return n;
        }
        return (par[n]=find(par[n]));
    }
    void merge(ll a, ll b){
        a=find(a), b=find(b);
        if(a==b){
            return;
        }
        if(size[a]<size[b]){
            a+=b, b=a-b, a-=b;
        }
        par[b]=a;
        size[a]+=size[b];
    }
};

class dijkstra{ // matrix form is similar
public:
    vi(ll)d, p;
    vi(bool)vis;
    ll s;
    dijkstra(ll S){
        s=S;
    }
    void dijkstraDense(const vi(vi(pi))&g) { // for max edges; O(v^2)
        ll n = g.size();
        d.assign(n, LLONG_MAX), p.assign(n, -1), vis.assign(n, false);
        d[s] = 0;
        for (ll i = 0; i < n; i++) {
            ll v = -1;
            for (ll j = 0; j < n; j++) {
                if (!vis[j] && (v == -1 || d[j] < d[v])){
                    v = j;
                }
            }
            if (d[v] == LLONG_MAX){
                break;
            }
            vis[v] = true;
            for (auto edge : g[v]) {
                ll to = edge.first, w = edge.second;
                if (d[v] + w < d[to]) {
                    d[to] = d[v] + w;
                    p[to] = v;
                }
            }
        }
    }
    void dijkstraSparse(const vi(vi(pi))&g) { // for min edges; O(elogn)
        ll n = g.size();
        d.assign(n, LLONG_MAX), p.assign(n, -1);
        d[s] = 0;
        priority_queue<pi, vector<pi>, greater<pi>> q;
        q.push({0, s});
        while (!q.empty()) {
            ll v = q.top().second, dist = q.top().first;
            q.pop();
            if (dist != d[v]){
                continue;
            }
            for (auto edge : g[v]) {
                ll to = edge.first, w = edge.second;
                if (d[v] + w < d[to]) {
                    d[to] = d[v] + w;
                    p[to] = v;
                    q.push({d[to], to});
                }
            }
        }
    }
    void getPath(ll t, vi(ll)&path) {
        for(ll v = t;; v = p[v]){
            path.pb(v);
            if(v==s){
                break;
            }
        }
        reverse(begin(path), end(path));
    }
};