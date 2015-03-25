#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>
#include <cmath>

#define EP 1e-10
#define N 1024040

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

struct SegmentNode {
    ll nBucc;

    bool upInvert;
    bool upBucc;
};

SegmentNode st[N*4];
bool A[N];

ll left(ll cur) { return cur << 1; }
ll right(ll cur) { return (cur << 1) + 1; }

void merge(SegmentNode &left, SegmentNode &right, SegmentNode &result) {
    result.nBucc = left.nBucc + right.nBucc;
}

void updateChildren(ll cur, ll L, ll R);

SegmentNode query(ll cur, ll L, ll R, ll LQ, ll RQ) {
    if (L >= LQ && R <= RQ)
        return st[cur];

    updateChildren(cur, L, R);
    ll M = (L+R)/2;

    if (M < LQ)
        return query(right(cur), M+1, R, LQ, RQ);

    if (M+1 > RQ)
        return query(left(cur), L, M, LQ, RQ);

    SegmentNode leftResult = query(left(cur), L, M, LQ, RQ);
    SegmentNode rightResult = query(right(cur), M+1, R, LQ, RQ);
    SegmentNode result;

    merge(leftResult, rightResult, result);

    return result;
}

void rangeUpdate(ll cur, ll L, ll R, ll Lbound, ll Rbound, bool invert, bool makeBucc) {
    if (L >= Lbound && R <= Rbound) {
        if (makeBucc) {
            st[cur].nBucc = R-L+1;
            st[cur].upInvert = false;
            st[cur].upBucc = true;
        }
        if (invert) {
            st[cur].nBucc = (R-L+1) - st[cur].nBucc;
            st[cur].upInvert = !st[cur].upInvert;
        }
    }
    else if (L <= Rbound && R >= Lbound) {
        updateChildren(cur, L, R);

        ll M = (L+R)/2;
        rangeUpdate(left(cur), L, M, Lbound, Rbound, invert, makeBucc);
        rangeUpdate(right(cur), M+1, R, Lbound, Rbound, invert, makeBucc);

        merge(st[left(cur)], st[right(cur)], st[cur]);
    }
}

void updateChildren(ll cur, ll L, ll R) {
    if (st[cur].upInvert || st[cur].upBucc) {
        ll M = (L+R)/2;
        rangeUpdate(left(cur), L, M, L, R, st[cur].upInvert, st[cur].upBucc);
        rangeUpdate(right(cur), M+1, R, L, R, st[cur].upInvert, st[cur].upBucc);

        st[cur].upInvert = false;
        st[cur].upBucc = false;
    }
}

void build(ll cur, ll L, ll R) {
    st[cur].upInvert = false;
    st[cur].upBucc = false;
    
    if (L == R) {
        st[cur].nBucc = A[L];
    }
    else {
        ll M = (L+R)/2;
        build(left(cur), L, M);
        build(right(cur), M+1, R);

        merge(st[left(cur)], st[right(cur)], st[cur]);
    }
}

void construct(ll length) {
    build(1, 0, length-1);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll nCases;
    cin >> nCases;

    for (ll cs = 1; cs <= nCases; ++cs) {
        ll M;
        cin >> M;

        vi T(M);
        vector<string> Pirates(M);
        ll length = 0;

        for (ll i = 0; i < M; ++i) {
            cin >> T[i] >> Pirates[i];
            length += T[i] * Pirates[i].size();
        }

        // this loop takes 1/3 of the computation time
        ll counter = 0;
        for (ll i = 0; i < M; ++i) {
            for (ll j = 0; j < T[i]; ++j) {
                for (ll k = 0; k < Pirates[i].size(); ++k) {
                    A[counter++] = Pirates[i][k] == '1';
                }
            }
        }

        // this takes about 3/6
        construct(length);

        ll Q;
        cin >> Q;

        // this takes about 1/6
        cout << "Case " << cs << ":" << endl;
        ll godCount = 1;
        for (ll i = 0; i < Q; ++i) {
            string type;
            cin >> type;

            ll a, b;
            cin >> a >> b;

            if (type == "F") {
                rangeUpdate(1, 0, length-1, a, b, false, true);
            }
            else if (type == "E") {
                rangeUpdate(1, 0, length-1, a, b, true, true);
            }
            else if (type == "I") {
                rangeUpdate(1, 0, length-1, a, b, true, false);
            }
            else {
                SegmentNode result = query(1, 0, length-1, a, b);
                cout << "Q" << godCount++ << ": " << result.nBucc << endl;
            }
        }
    }

    return 0;
}
