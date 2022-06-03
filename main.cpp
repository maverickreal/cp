#include "iostream"
#include "vector"
#include "list"
#include "limits.h"
#include "stack"
#include "unordered_map"
#include "unordered_set"
#include "math.h"
#include "algorithm"
#include "queue"
#include "functional"
#include "numeric"
#include "segmentTree.h"

using namespace std;

template<typename a, typename b, typename c>
class tri {
public:
    a x;
    b y;
    c z;
    tri(a x, b y, c z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    tri() {
        this->x = *(new a);
        this->y = *(new b);
        this->z = *(new c);
    }
};

typedef long long ll;
typedef long double ld;
typedef vector<ll> vi;
#define endl '\n'
static const ll mod = 1e9;

vector<bool>primes;

void setPrimes(ll n);

vector<vector<ll>>getChildren(const vector<ll>& v);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll t = 1;
    //cin >> t;
    while (t--) {
        ll sz;
        cin >> sz;
        vector<ll>v(sz);
        for (ll& i : v)
            cin >> i;
        st tree(v);
        ll q;
        cin >> q;
        while (q--) {
            ll a, b;
            char ch;
            cin >> a >> b >> ch;
            if (ch == 'u')
                tree.updateValue(a, b);
            else if (ch == 'g')
                cout << tree.getSum(a, b) << endl;
        }
    }
    return 0;
}

void setPrimes(ll n) {
    vector<bool>v(n + 1, true);
    v[0] = v[1] = false;
    for (ll i = 2;i * i <= n;i++) {
        if (v[i]) {
            for (ll j = i;j * i <= n;++j)
                v[j * i] = false;
        }
    }
    primes = v;
}

vector<vector<ll>>getChildren(const vector<ll>& v) {
    ll n = v.size();
    vector<vector<ll>>res(n);
    for (ll i = 0;i < n;++i) {
        ll node = i + 1, par = v[i];
        if (par == -1)continue;
        res[par - 1].push_back(node);
    }
    return res;
}