#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

struct SegmentNode {
    ll L, R;

    ll nBucc;
    ll nBar;

    bool upInvert;
    bool upBucc;
    bool upBar;

    SegmentNode(ll L, ll R, ll nBucc, ll nBar) : L(L), R(R), nBucc(nBucc), nBar(nBar) {
        upInvert = false;
        upBucc = false;
        upBar = false;
    }

    SegmentNode() {}
};

struct SegmentTree {
    vector<SegmentNode> st;

    ll left(ll cur) { return cur << 1; }
    ll right(ll cur) { return (cur << 1) + 1; }

    SegmentNode merge(SegmentNode &left, SegmentNode &right) {
        return SegmentNode(left.L, right.R, left.nBucc+right.nBucc, left.nBar+right.nBar);   
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

        return merge(leftResult, rightResult);
    }

    void rangeUpdate(ll cur, ll Lbound, ll Rbound, bool invert, bool makeBucc, bool makeBar) {
        if (st[cur].L >= Lbound && st[cur].R <= Rbound) {
            if (makeBucc) {
                st[cur].nBucc = st[cur].nBucc + st[cur].nBar;
                st[cur].nBar = 0;
                st[cur].upInvert = false;
                st[cur].upBucc = true;
                st[cur].upBar = false;
            }
            if (makeBar) {
                st[cur].nBar = st[cur].nBucc + st[cur].nBar;
                st[cur].nBucc = 0;
                st[cur].upInvert = false;
                st[cur].upBar = true;
                st[cur].upBucc = false;
            }
            if (invert) {
                swap(st[cur].nBucc, st[cur].nBar);
                st[cur].upInvert = true;
            }
        }
        else if (st[cur].L <= Rbound && st[cur].R >= Lbound) {
            updateChildren(cur);

            rangeUpdate(left(cur), Lbound, Rbound, invert, makeBucc, makeBar);
            rangeUpdate(right(cur), Lbound, Rbound, invert, makeBucc, makeBar);

            st[cur] = merge(st[left(cur)], st[right(cur)]);
        }
    }

    void updateChildren(ll cur) {
        rangeUpdate(left(cur), st[cur].L, st[cur].R, st[cur].upInvert, st[cur].upBucc, st[cur].upBar);
        rangeUpdate(right(cur), st[cur].L, st[cur].R, st[cur].upInvert, st[cur].upBucc, st[cur].upBar);

        st[cur].upInvert = false;
        st[cur].upBucc = false;
        st[cur].upBar = false;
    }

    void build(ll cur, ll L, ll R, string &A) {
        if (L == R) {
            st[cur] = SegmentNode(L, R, A[L] == '1', A[L] == '0');
        }
        else {
            build(left(cur), L, (L+R)/2, A);
            build(right(cur), (L+R)/2+1, R, A);

            st[cur] = merge(st[left(cur)], st[right(cur)]);
        }
    }

    SegmentTree(string &A) {
        st = vector<SegmentNode>((A.size()+1)*3);
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

        stringstream ss;
        for (ll i = 0; i < M; ++i) {
            ll T;
            cin >> T;
            
            string Pirates;
            cin >> Pirates;

            for (ll j = 0; j < T; ++j) {
                ss << Pirates;
            }
        }

        string A;
        ss >> A;

        //cerr << "building" << endl;
        SegmentTree stree(A);
        //cerr << "done" << endl;

        ll Q;
        cin >> Q;

        //printf("Case %lld:\n", cs);
        cout << "Case " << cs << ":" << endl;
        ll godCount = 1;
        for (ll i = 0; i < Q; ++i) {
            string type;
            cin >> type;

            ll a, b;
            cin >> a >> b;

            if (type == "F") {
                stree.rangeUpdate(1, a, b, false, true, false);
            }
            else if (type == "E") {
                stree.rangeUpdate(1, a, b, false, false, true);
            }
            else if (type == "I") {
                stree.rangeUpdate(1, a, b, true, false, false);
            }
            else {
                SegmentNode result = stree.query(1, a, b);
                cout << "Q" << godCount++ << ": " << result.nBucc << endl;
                //printf("Q%lld: %lld\n", godCount++, result.nBucc);
            }
        }
    }

    return 0;
}
