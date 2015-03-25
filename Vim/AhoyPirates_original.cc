#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>
#include <cmath>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

struct SegmentNode {
    ll L, R;

    ll nBucc;

    bool upInvert;
    bool upBucc;
};

struct SegmentTree {
    vector<SegmentNode> st;

    ll left(ll cur) { return cur << 1; }
    ll right(ll cur) { return (cur << 1) + 1; }

    void merge(SegmentNode &left, SegmentNode &right, SegmentNode &result) {
        result.nBucc = left.nBucc + right.nBucc;
    }

    SegmentNode query(ll cur, ll LQ, ll RQ) {
        if (st[cur].L >= LQ && st[cur].R <= RQ)
            return st[cur];

        updateChildren(cur);

        if (st[left(cur)].R < LQ)
            return query(right(cur), LQ, RQ);

        if (st[right(cur)].L > RQ)
            return query(left(cur), LQ, RQ);

        SegmentNode leftResult = query(left(cur), LQ, RQ);
        SegmentNode rightResult = query(right(cur), LQ, RQ);
        SegmentNode result;

        merge(leftResult, rightResult, result);

        return result;
    }

    void rangeUpdate(ll cur, ll Lbound, ll Rbound, bool invert, bool makeBucc) {
        if (st[cur].L >= Lbound && st[cur].R <= Rbound) {
            if (makeBucc) {
                st[cur].nBucc = st[cur].R-st[cur].L+1;
                st[cur].upInvert = false;
                st[cur].upBucc = true;
            }
            if (invert) {
                st[cur].nBucc = (st[cur].R-st[cur].L+1) - st[cur].nBucc;
                st[cur].upInvert = !st[cur].upInvert;
            }
        }
        else if (st[cur].L <= Rbound && st[cur].R >= Lbound) {
            updateChildren(cur);

            rangeUpdate(left(cur), Lbound, Rbound, invert, makeBucc);
            rangeUpdate(right(cur), Lbound, Rbound, invert, makeBucc);

            merge(st[left(cur)], st[right(cur)], st[cur]);
        }
    }

    void updateChildren(ll cur) {
        if (st[cur].upInvert || st[cur].upBucc) {
            rangeUpdate(left(cur), st[cur].L, st[cur].R, st[cur].upInvert, st[cur].upBucc);
            rangeUpdate(right(cur), st[cur].L, st[cur].R, st[cur].upInvert, st[cur].upBucc);

            st[cur].upInvert = false;
            st[cur].upBucc = false;
        }
    }

    void build(ll cur, ll L, ll R, vb &A) {
        st[cur].L = L;
        st[cur].R = R;
        
        if (L == R) {
            st[cur].nBucc = A[L];
        }
        else {
            build(left(cur), L, (L+R)/2, A);
            build(right(cur), (L+R)/2+1, R, A);

            merge(st[left(cur)], st[right(cur)], st[cur]);
        }
    }

    SegmentTree(vb &A) {
        st.resize(A.size()*4);
        build(1, 0, A.size()-1, A);
    }
};



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
        vb A(length);
        ll counter = 0;
        for (ll i = 0; i < M; ++i) {
            for (ll j = 0; j < T[i]; ++j) {
                for (ll k = 0; k < Pirates[i].size(); ++k) {
                    A[counter++] = Pirates[i][k] == '1';
                }
            }
        }

        // this takes about 3/6
        SegmentTree tree(A);

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
                tree.rangeUpdate(1, a, b, false, true);
            }
            else if (type == "E") {
                tree.rangeUpdate(1, a, b, true, true);
            }
            else if (type == "I") {
                tree.rangeUpdate(1, a, b, true, false);
            }
            else {
                SegmentNode result = tree.query(1, a, b);
            //    cout << "Q" << godCount++ << ": " << result.nBucc << endl;
            }
        }
    }

    return 0;
}
