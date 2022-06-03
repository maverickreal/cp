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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;


class st {
private:
    vi tree, arr;

    void build(ll pos, ll s, ll e) {
        if (s == e) {
            tree[pos] = arr[s];
            return;
        }
        ll mid = s + ((e - s) >> 1);
        build((pos << 1) + 1, s, mid);
        build((pos << 1) + 2, mid + 1, e);
        tree[pos] = tree[(pos << 1) + 1] + tree[(pos << 1) + 2];
    }
public:
    st(const vi& v) {
        arr = v;
        tree.resize(4 * v.size());
        build(0, 0, v.size() - 1);
    }

    vi getArr() {
        return arr;
    }

    ll getSumUtil(ll s, ll e, ll qs, ll qe, ll node) {
        if (qs <= s && qe >= e)
            return tree[node];

        if (e < qs || s > qe)
            return 0;

        ll mid = s + ((e - s) >> 1);
        return getSumUtil(s, mid, qs, qe, (node << 1) + 1) +
            getSumUtil(mid + 1, e, qs, qe, (node << 1) + 2);
    }

    ll getSum(ll qs, ll qe) {
        if (qs < 0 || qe > arr.size() - 1 || qs > qe)
            return -1;
        return getSumUtil(0, arr.size() - 1, qs, qe, 0);
    }

    void updateValueUtil(ll ss, ll se, ll i, ll diff, ll si) {
        if (i < ss || i > se)
            return;
        tree[si] += diff;
        if (se == ss)
            return;
        ll mid = ss + ((se - ss) >> 1);
        updateValueUtil(ss, mid, i, diff, (si << 1) + 1);
        updateValueUtil(mid + 1, se, i, diff, (si << 1) + 2);
    }

    void updateValue(ll i, ll new_val) {
        if (i < 0 || i > arr.size() - 1)return;
        ll diff = new_val - arr[i];
        arr[i] = new_val;
        updateValueUtil(0, arr.size() - 1, i, diff, 0);
    }
};