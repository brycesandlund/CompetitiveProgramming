#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

// BEGIN
// Segment Tree with lazy propagation. This solves
// AhoyPirates on UVa Online Judge in 1.172 seconds.
// To use, you only need to change SegmentNode data, 
// the merge function, update, and initialization;
// the functions are written in such a way as to handle everything else.
// If range updates are not necessary, 
// ignore the updateVal and rangeUpdate function.
// The following implementation is an example for RMQ.

#define MAXN 100100 // the maximum input length of the sequnece, good idea to add 10 or so to this
#define INF 1000000000000LL
#define x first
#define y second
#define f first
#define s second

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

vii points;
ll n, q;

struct SegmentNode {
    // segment data
    vii x_coords;
    vii y_coords;
};

SegmentNode st[MAXN*4];

size_t left(size_t cur) { return cur << 1; }
size_t right(size_t cur) { return (cur << 1) + 1; }

vii mergeVs(vii one, vii two) {
    one.insert(one.end(), two.begin(), two.end());
    sort(one.begin(), one.end());

    if (one.size() > 4) {
        vii finalV(4);
        finalV[0] = one[0];
        finalV[1] = one[1];
        finalV[2] = one[one.size()-2];
        finalV[3] = one[one.size()-1];
        return finalV;
    }
    else {
        return one;
    }
}

// create merging function here
void merge(SegmentNode &left, SegmentNode &right, SegmentNode &result) {
    result.x_coords = mergeVs(left.x_coords, right.x_coords);
    result.y_coords = mergeVs(left.y_coords, right.y_coords);
}

// merge handles all querying, no changes needed here
// note that when calling any segment funcitons in main,
// the first three parameters will be 1, 0, length-1
SegmentNode query(size_t cur, size_t L, size_t R, size_t LQ, size_t RQ) {
    if (L >= LQ && R <= RQ)
        return st[cur];

    size_t M = (L+R)/2;

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

void build(size_t cur, size_t L, size_t R) {
    if (L == R) {
        // initialize single value here
        st[cur].x_coords = vii(1, ii(points[L].x, L));
        st[cur].y_coords = vii(1, ii(points[L].y, L));
    }
    else {
        size_t M = (L+R)/2;
        build(left(cur), L, M);
        build(right(cur), M+1, R);

        merge(st[left(cur)], st[right(cur)], st[cur]);
    }
}

ll check(set<ii> &solutionSet) {
    ll max_x = -INF, min_x = INF, max_y = -INF, min_y = INF;
    for (auto it = solutionSet.begin(); it != solutionSet.end(); ++it) {
        max_x = max(max_x, it->x);
        min_x = min(min_x, it->x);
        max_y = max(max_y, it->y);
        min_y = min(min_y, it->y);
    }

    return max(max_x - min_x, max_y - min_y);
}


int main() {
    cin >> n >> q;

    points = vii(n);
    for (ll i = 0; i < n; ++i) {
        cin >> points[i].f >> points[i].s;
    }

    build(1, 0, n-1);

    for (ll i = 0; i < q; ++i) {
        ll a, b;
        cin >> a >> b;
        --a; --b;

        SegmentNode ans = query(1, 0, n-1, a, b);
        set<ii> boundPts;
        for (ll j = 0; j < ans.x_coords.size(); ++j) {
            boundPts.insert(points[ans.x_coords[j].s]);
        }
        for (ll j = 0; j < ans.y_coords.size(); ++j) {
            boundPts.insert(points[ans.y_coords[j].s]);
        }

        ll best = INF;
        for (auto it = boundPts.begin(); it != boundPts.end(); ++it) {
            set<ii> solutionSet;
            for (auto it2 = boundPts.begin(); it2 != boundPts.end(); ++it2) {
                if (it2 == it) continue;

                solutionSet.insert(*it2);
            }

            best = min(best, check(solutionSet));
        }

        cout << best << endl;
    }
}
