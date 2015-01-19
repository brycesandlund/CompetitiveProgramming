    #include <iostream>
    #include <vector>
    #include <string>

    using namespace std;

    typedef long long LL;
    typedef vector<LL> vn;

    vn add(vn one, vn two)
    {
        for (size_t i = 0; i < 3; ++i)
            one[i] += two[i];

        return one;
    }

    vn shift(vn &arr, LL amount)
    {
        vn result(3, 0);

        for (size_t i = 0; i < 3; ++i)
            result[(i+amount)%3] = arr[i];

        return result;
    }

    struct SegmentNode
    {
        vn leftEnd, rightEnd;
        LL whole;
        LL numD3;
        size_t L, R;

        SegmentNode() {}

        SegmentNode(vn leftEnd, vn rightEnd, LL whole, LL numD3, size_t L, size_t R)
            : leftEnd(leftEnd), rightEnd(rightEnd), whole(whole), numD3(numD3), L(L), R(R) {}
    };

    struct SegmentTree
    {
        vector<SegmentNode> st;

        size_t left(size_t cur) { return cur << 1; }
        size_t right(size_t cur) { return (cur << 1) + 1; }

        SegmentNode merge(SegmentNode &left, SegmentNode &right)
        {
            vn leftEnd = add(left.leftEnd, shift(right.leftEnd, left.whole));
            ++leftEnd[left.whole];

            vn rightEnd = add(right.rightEnd, shift(left.rightEnd, right.whole)); 
            ++rightEnd[right.whole];

            LL whole = (left.whole + right.whole) % 3;

            LL numD3 = left.numD3 + right.numD3;
            for (size_t i = 0; i < 3; ++i)
                numD3 += left.rightEnd[i] * right.leftEnd[(3-i)%3];

            numD3 += left.rightEnd[(3-right.whole)%3];
            numD3 += right.leftEnd[(3-left.whole)%3];
            
            if (whole == 0)
                ++numD3;

            return SegmentNode(leftEnd, rightEnd, whole, numD3, left.L, right.R);
        }
        
        void build(size_t cur, size_t L, size_t R, vn &A)
        {
            if (L == R)
            {
                LL numD3 = (A[L])%3 == 0 ? 1 : 0;
                st[cur] = SegmentNode(vn(3, 0), vn(3, 0), A[L]%3, numD3, L, R);
            }
            else
            {
                build(left(cur), L, (L+R)/2, A);
                build(right(cur), (L+R)/2+1, R, A);

                st[cur] = merge(st[left(cur)], st[right(cur)]);
            }
        }

        SegmentTree(vn &A)
        {
            st = vector<SegmentNode>(A.size()*4);
            build(1, 0, A.size()-1, A);
        }

        SegmentNode query(size_t cur, size_t LQ, size_t RQ)
        {
            if (st[cur].L >= LQ && st[cur].R <= RQ)
                return st[cur];

            if (st[left(cur)].R < LQ)
                return query(right(cur), LQ, RQ);

            if (st[right(cur)].L > RQ)
                return query(left(cur), LQ, RQ);

            SegmentNode leftResult = query(left(cur), LQ, RQ);
            SegmentNode rightResult = query(right(cur), LQ, RQ);

            SegmentNode result = merge(leftResult, rightResult);
            
            return result;
        }

        void update(size_t cur, size_t idx, LL val)
        {
            if (st[cur].L == idx && st[cur].R == idx)
            {
                st[cur].whole = val%3;
                st[cur].numD3 = val%3 == 0 ? 1 : 0;
            }
            else if (st[cur].L <= idx && st[cur].R >= idx)
            {
                update(left(cur), idx, val);
                update(right(cur), idx, val);
                
                st[cur] = merge(st[left(cur)], st[right(cur)]);
            }
        }
    };

    int main()
    {
        ios_base::sync_with_stdio(false);
        cin.tie(0);

        LL N, M;
        cin >> N >> M;

        string line;
        cin >> line;

        vn A(N);
        for (size_t i = 0; i < N; ++i)
        {
            A[i] = line[i] - '0';
        }

        SegmentTree tree(A);

        for (size_t i = 0; i < M; ++i)
        {
            LL type;
            cin >> type;

            if (type == 1)
            {
                size_t X;
                LL Y;
                cin >> X >> Y;
                tree.update(1, X-1, Y);
            }
            else
            {
                size_t C, D;
                cin >> C >> D;
                SegmentNode result = tree.query(1, C-1, D-1);
                cout << result.numD3 << endl;
            }
        }
    }
