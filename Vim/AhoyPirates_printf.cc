#include <cstdio>
#include <vector>
#include <sstream>
#include <cmath>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll logb2(ll N) {
    return (log(N)+log(2)-EP) / log(2);
}

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
    //    cerr << cur << " " << LQ << " " << RQ << endl;
        
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
        rangeUpdate(left(cur), st[cur].L, st[cur].R, st[cur].upInvert, st[cur].upBucc);
        rangeUpdate(right(cur), st[cur].L, st[cur].R, st[cur].upInvert, st[cur].upBucc);

        st[cur].upInvert = false;
        st[cur].upBucc = false;
    }

    void build(ll cur, ll L, ll R, string &A) {
        st[cur].L = L;
        st[cur].R = R;
        
        if (L == R) {
            st[cur].nBucc = A[L] == '1';
        }
        else {
            build(left(cur), L, (L+R)/2, A);
            build(right(cur), (L+R)/2+1, R, A);

            merge(st[left(cur)], st[right(cur)], st[cur]);
        }
    }

    SegmentTree(string &A) {
        st.resize(1 << logb2(A.size()*2+1));
        build(1, 0, A.size()-1, A);
    }
};

int main() {
    ll nCases;
    scanf("%lld", &nCases);

    for (ll cs = 1; cs <= nCases; ++cs) {
        ll M;
        scanf("%lld", &M);

        stringstream ss;
        for (ll i = 0; i < M; ++i) {
            ll T;
            scanf("%lld", &T);

            char PiratesCstr[60];
            scanf("%s", PiratesCstr);
            string Pirates(PiratesCstr);            

           // printf("%s\n", Pirates.c_str());

            for (ll j = 0; j < T; ++j) {
                ss << Pirates;
            }
        }

        string A;
        ss >> A;

        //cerr << "building" << endl;
//        SegmentTree tree(A);
        //cerr << "done" << endl;

        ll Q;
        scanf("%lld", &Q);

        printf("Case %lld:\n", cs);
        ll godCount = 1;
        for (ll i = 0; i < Q; ++i) {
            char type;
            ll a, b;
            
            scanf("%c %lld %lld", &type, &a, &b);

      //      cerr << "query " << i << endl;

           /* if (type == "F") {
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
                cout << "Q" << godCount++ << ": " << result.nBucc << endl;
            }*/
        }
    }

    return 0;
}
