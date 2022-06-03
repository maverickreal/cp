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
typedef TreeNode tn;
#define ListNode ln;
#define endl '\n'
const ll mod = 1e9;

ll retAns = 1;

tri<ll, ll, ll> func(tn* rt) {
    tri<ll, ll, ll>res = { 1,rt->data, rt->data };
    if (!rt->left && !rt->right)
        return res;
    if (rt->left) {
        tri<ll, ll, ll> l = func(rt->left);
        if (!l.x || l.y >= rt->data)
            return tri<ll, ll, ll>(0, rt->data, rt->data);
        res.x += l.x;
        res.z = l.z;
    }
    if (rt->right) {
        tri<ll, ll, ll> r = func(rt->right);
        if (!r.x || r.z <= rt->data)
            return tri<ll, ll, ll>(0, rt->data, rt->data);
        res.x += r.x;
        res.y = r.y;
    }
    retAns = max(retAns, res.x);
    return res;
}