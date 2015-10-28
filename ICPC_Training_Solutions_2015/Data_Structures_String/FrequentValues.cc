#include <iostream>
#include <vector>

using namespace std;

#define MAXN 100010

typedef long long ll;
typedef vector<ll> vi;

struct SegmentNode {
    ll max_occur;
    ll l_val;
    ll r_val;
    ll l_occur;
    ll r_occur;
};

SegmentNode st[MAXN*4];
ll A[MAXN];

ll left(ll cur) { return cur << 1; }
ll right(ll cur) { return (cur << 1) + 1; }

void merge(SegmentNode &left, SegmentNode &right, SegmentNode &result) {
    result.l_val = left.l_val;
    result.l_occur = left.l_occur;
    result.r_val = right.r_val;
    result.r_occur = right.r_occur;
    
    result.max_occur = max(left.max_occur, right.max_occur);
    if (left.r_val == right.l_val) {
        result.max_occur = max(result.max_occur, left.r_occur + right.l_occur);
        
        if (left.l_val == left.r_val) {
            result.l_occur += right.l_occur;
        }
        if (right.l_val == right.r_val) {
            result.r_occur += left.r_occur;
        }
    }
}

SegmentNode query(ll cur, ll L, ll R, ll LQ, ll RQ) {
    if (L >= LQ && R <= RQ)
        return st[cur];

    ll M = (L+R)/2;

    if (M < LQ)
        return query(right(cur), M+1, R, LQ, RQ);

    if (M+1 > RQ)
        return query(left(cur), L, M, LQ, RQ);

    SegmentNode left_result = query(left(cur), L, M, LQ, RQ);
    SegmentNode right_result = query(right(cur), M+1, R, LQ, RQ);
    SegmentNode result;

    merge(left_result, right_result, result);

    return result;
}

void build(ll cur, ll L, ll R) {
    if (L == R) {
        st[cur].max_occur = 1;
        st[cur].l_val = A[L];
        st[cur].r_val = A[L];
        st[cur].l_occur = 1;
        st[cur].r_occur = 1;
    }
    else {
        ll M = (L+R)/2;
        build(left(cur), L, M);
        build(right(cur), M+1, R);

        merge(st[left(cur)], st[right(cur)], st[cur]);
    }
}

int main() {
    ll n, q;
    for (ll cs = 1; cin >> n && n && cin >> q; ++cs) {
        for (ll i = 0; i < n; ++i) {
            cin >> A[i];
        }

        build(1, 0, n-1);

        for (ll i = 0; i < q; ++i) {
            ll LQ, RQ;
            cin >> LQ >> RQ;
            --LQ;
            --RQ;
            cout << query(1, 0, n-1, LQ, RQ).max_occur << endl;
        }
    }
    return 0;
}
