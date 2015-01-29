#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;


struct SegmentNode {
    ll L, R;

    // segment data
    ll maxVal;

    // update data
    ll updateVal;

    SegmentNode(ll L, ll R, ll maxVal) : L(L), R(R), maxVal(maxVal) 
    {
        // initialize update values to no updates necessary
        updateVal = 0;
    }

    SegmentNode() {}
};

struct SegmentTree {
    vector<SegmentNode> st;

    ll left(ll cur) { return cur << 1; }
    ll right(ll cur) { return (cur << 1) + 1; }

    // create merging function here
    SegmentNode merge(SegmentNode &left, SegmentNode &right) {
        return SegmentNode(left.L, right.R, max(left.maxVal, right.maxVal));
    }

    void updateChildren(ll cur) {
        rangeUpdate(left(cur), st[cur].L, st[cur].R, st[cur].updateVal);
        rangeUpdate(right(cur), st[cur].L, st[cur].R, st[cur].updateVal);

        // reset update vals
        st[cur].updateVal = 0;
    }

    // merge handles all querying, no changes needed here
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

    // do not use if rangeUpdate is needed
    void update(ll cur, ll idx, ll val) {
        if (st[cur].L == idx && st[cur].R == idx) {
            // write update of single value here
            st[cur].maxVal = val;
        }
        else if (st[cur].L <= idx && st[cur].R >= idx) {
            update(left(cur), idx, val);
            update(right(cur), idx, val);

            st[cur] = merge(st[left(cur)], st[right(cur)]);
        }
    }

    // only implement if necessary
    void rangeUpdate(ll cur, ll Lbound, ll Rbound, ll val) {
        if (st[cur].L >= Lbound && st[cur].R <= Rbound) {
            // implement range update here
            st[cur].maxVal += val;

            // set update vals here
            st[cur].updateVal += val;
        }
        else if (st[cur].L <= Rbound && st[cur].R >= Lbound) {
            updateChildren(cur);

            rangeUpdate(left(cur), Lbound, Rbound, val);
            rangeUpdate(right(cur), Lbound, Rbound, val);

            st[cur] = merge(st[left(cur)], st[right(cur)]);
        }
    }

    void build(ll cur, ll L, ll R, vi &A) {
        if (L == R) {
            // initialize single value here
            st[cur] = SegmentNode(L, R, A[L]);
        }
        else {
            build(left(cur), L, (L+R)/2, A);
            build(right(cur), (L+R)/2+1, R, A);

            st[cur] = merge(st[left(cur)], st[right(cur)]);
        }
    }

    SegmentTree(vi &A) {
        st = vector<SegmentNode>(A.size()*4);
        build(1, 0, A.size()-1, A);
    }
};

int main() {
    ll N = 10;
    int vals[] = {0, 42, 3, 4, 5, 983, 48, 28, 59, 1};

    vi A(vals, vals+N);

    SegmentTree tree(A);

    bool testLazy = true;

    if (!testLazy) {
        cout << tree.query(1, 0, 3).maxVal << endl; //42
        cout << tree.query(1, 2, 4).maxVal << endl; //5
        
        tree.update(1, 1, -10); //42 -> -10
        cout << tree.query(1, 0, 3).maxVal << endl; //4
        cout << tree.query(1, 0, 9).maxVal << endl; //983

        tree.update(1, 5, 80); //983 -> 80
        cout << tree.query(1, 0, 9).maxVal << endl; //80
        cout << tree.query(1, 6, 8).maxVal << endl; //59
    }
    else {
        cout << tree.query(1, 0, 3).maxVal << endl; //42
        cout << tree.query(1, 2, 4).maxVal << endl; //5

        tree.rangeUpdate(1, 2, 4, 40); //3, 4, 5 -> 43, 44, 45

        cout << tree.query(1, 0, 3).maxVal << endl; //44
        cout << tree.query(1, 0, 9).maxVal << endl; //983

        tree.rangeUpdate(1, 0, 9, 10); //everything +10
        cout << tree.query(1, 0, 9).maxVal << endl; //993
        cout << tree.query(1, 6, 8).maxVal << endl; //69
    }

    return 0;
}
