#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

struct SegmentTree {
    vi nBucc;
    vi nBar;
    vb upInvert;
    vb upBucc;
    vb upBar;

    ll left(ll cur) { return cur << 1; }
    ll right(ll cur) { return (cur << 1) + 1; }

    void merge(ll lnBucc, ll lnBar, ll rnBucc, ll rnBar, ll &nnBucc, ll &nnBar) {
        nnBucc = lnBucc + rnBucc;
        nnBar = lnBar + rnBar;
    }

    ll query(ll cur, ll L, ll R, ll LQ, ll RQ) {
        //cerr << cur << " " << L << " " << R << endl;
    
        if (L >= LQ && R <= RQ)
            return nBucc[cur];

        updateChildren(cur, L, R);

        if ((L+R)/2 < LQ)
            return query(right(cur), (L+R)/2+1, R, LQ, RQ);

        if ((L+R)/2+1 > RQ)
            return query(left(cur), L, (L+R)/2, LQ, RQ);

        return query(left(cur), L, (L+R)/2, LQ, RQ) + query(right(cur), (L+R)/2+1, R, LQ, RQ);
    }

    void rangeUpdate(ll cur, ll L, ll R, ll Lbound, ll Rbound, bool invert, bool makeBucc, bool makeBar) {
        if (L >= Lbound && R <= Rbound) {
            if (makeBucc) {
                nBucc[cur] = nBucc[cur] + nBar[cur];
                nBar[cur] = 0;
                upInvert[cur] = false;
                upBucc[cur] = true;
                upBar[cur] = false;
            }
            if (makeBar) {
                nBar[cur] = nBucc[cur] + nBar[cur];
                nBucc[cur] = 0;
                upInvert[cur] = false;
                upBar[cur] = true;
                upBucc[cur] = false;
            }
            if (invert) {
                swap(nBucc[cur], nBar[cur]);
                upInvert[cur] = true;
            }
        }
        else if (L <= Rbound && R >= Lbound) {
            updateChildren(cur, L, R);

            rangeUpdate(left(cur), L, (L+R)/2, Lbound, Rbound, invert, makeBucc, makeBar);
            rangeUpdate(right(cur), (L+R)/2+1, R, Lbound, Rbound, invert, makeBucc, makeBar);

            merge(nBucc[left(cur)], nBar[left(cur)], nBucc[right(cur)], nBar[right(cur)], nBucc[cur], nBar[cur]);
        }
    }

    void updateChildren(ll cur, ll L, ll R) {
        rangeUpdate(left(cur), L, (L+R)/2, L, R, upInvert[cur], upBucc[cur], upBar[cur]);
        rangeUpdate(right(cur), (L+R)/2+1, R, L, R, upInvert[cur], upBucc[cur], upBar[cur]);

        upInvert[cur] = false;
        upBucc[cur] = false;
        upBar[cur] = false;
    }

    void build(ll cur, ll L, ll R, string &A) {
        if (L == R) {
            nBucc[cur] = A[L] == '1';
            nBar[cur] = A[L] == '0';
        }
        else {
            build(left(cur), L, (L+R)/2, A);
            build(right(cur), (L+R)/2+1, R, A);

            merge(nBucc[left(cur)], nBar[left(cur)], nBucc[right(cur)], nBar[right(cur)], nBucc[cur], nBar[cur]);
        }
    }

    SegmentTree(string &A) {
        nBucc = vi(A.size()*4);
        nBar = vi(A.size()*4);
        upBucc = vb(A.size()*4);
        upBar = vb(A.size()*4);
        upInvert = vb(A.size()*4);
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

        cout << "Case " << cs << ":" << endl;
        ll godCount = 1;
        for (ll i = 0; i < Q; ++i) {
            string type;
            cin >> type;

            ll a, b;
            cin >> a >> b;

          //  cerr << "here" << endl;

            if (type == "F") {
                stree.rangeUpdate(1, 0, A.size()-1, a, b, false, true, false);
            }
            else if (type == "E") {
                stree.rangeUpdate(1, 0, A.size()-1, a, b, false, false, true);
            }
            else if (type == "I") {
                stree.rangeUpdate(1, 0, A.size()-1, a, b, true, false, false);
            }
            else {
                cout << "Q" << godCount++ << ": " << stree.query(1, 0, A.size()-1, a, b) << endl;
            }
        }
    }

    return 0;
}
