#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

#define EP 1e-10
#define N 20004
#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<string> vs;

vs Pirates;
vii idxAndStr;

struct SegmentNode {
    ll L, R;

    ll nBucc;
    ll stringIdx;
    string myPirates;

    bool upInvert;
    bool upBucc;

    // precondition: node is at least partially within [LQ, RQ]
    bool boundaryWithin(ll LQ, ll RQ) {
        return (!pirates.empty() || stringIdx != -1);
    }

    // precondition: node is boundaryWithin [LQ, RQ]
    SegmentNode count(ll LQ, ll RQ) {
        ll S = max(0, LQ-L);
        ll E = min(pirates.size(), RQ-L);

        SegmentNode newNode;
        newNode.L = S;
        newNode.R = E;
        newNode.nBucc = 0;
        string ref = myPirates.empty() ? Pirates[stringIdx] : myPirates;
        
        for (ll i = S; i < E; ++i) {
            if (ref[i] == '1')
                ++newNode.nBucc;
        }

        return newNode;
    }
};

SegmentNode st[N*4];

ll left(ll cur) { return cur << 1; }
ll right(ll cur) { return (cur << 1) + 1; }

void merge(SegmentNode &left, SegmentNode &right, SegmentNode &result) {
    result.nBucc = left.nBucc + right.nBucc;
}

void updateChildren(ll cur);

SegmentNode query(ll cur, ll LQ, ll RQ) {
    if (st[cur].L >= LQ && st[cur].R <= RQ)
        return st[cur];

    if (st[cur].boundaryWithin(LQ, RQ)) {
        return st[cur].count(LQ, RQ);
    }

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

vii::iterator getStr(ll idx) {
    return lower_bound(idxAndStr.begin(), idxAndStr.end(), make_pair(idx, INF));
}

bool same(ll L, ll R) {
    return getStr(L) == getStr(R);
}

void build(ll cur, ll L, ll R) {
    st[cur].L = L;
    st[cur].R = R;
    st[cur].upInvert = false;
    st[cur].upBucc = false;
 
    if (same(L, R)) {
        st[cur].
    }   
    if (L == R) {
        st[cur].nBucc = A[L];
    }
    else {
        build(left(cur), L, (L+R)/2);
        build(right(cur), (L+R)/2+1, R);

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
        Pirates.resize(M);
        idxAndStr.clear();
        ll length = 0;

        for (ll i = 0; i < M; ++i) {
            cin >> T[i] >> Pirates[i];
            
            for (ll j = 0; j < T[i]; ++j) {
                idxAndStr.push_back(ii(length, i));
                length += Pirates[i].size();
            }
        }

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
                rangeUpdate(1, a, b, false, true);
            }
            else if (type == "E") {
                rangeUpdate(1, a, b, true, true);
            }
            else if (type == "I") {
                rangeUpdate(1, a, b, true, false);
            }
            else {
                SegmentNode result = query(1, a, b);
                cout << "Q" << godCount++ << ": " << result.nBucc << endl;
            }
        }
    }

    return 0;
}
