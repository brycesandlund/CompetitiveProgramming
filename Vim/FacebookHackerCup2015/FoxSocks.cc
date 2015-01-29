#include <iostream>
#include <cstdio>
#include <vector>

#define Z 1000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

struct SegmentNode;
SegmentNode* merge(SegmentNode* left, SegmentNode* right);

struct SegmentNode
{
    ll total;
    ll numOddEven;
    ll numOddOdd;
    ll upFlat, upStag;
    bool empty;
    ll L, R;
    SegmentNode *left;
    SegmentNode *right;
    
    SegmentNode(ll total, ll numOddEven, ll numOddOdd, ll L, ll R, SegmentNode* left, SegmentNode* right) : 
    total(total), numOddEven(numOddEven), numOddOdd(numOddOdd), L(L), R(R), left(left), right(right)
    {
        upFlat = 0;
        upStag = 0;
        empty = false;
    }

    void updateChildren()
    {
        if (empty)
        {
            left->emptyRange(L, R);
            right->emptyRange(L, R);

            empty = false;
        }

        if (upFlat != 0 || upStag != 0)
        {
            left = left->rangeUpdate(L, R, upFlat, upStag);
            right = right->rangeUpdate(L, R, upFlat, upStag);

            upFlat = 0;
            upStag = 0;
        }

    }

    SegmentNode* rangeUpdate(ll Lbound, ll Rbound, ll flat, ll stag)
    {
        //cerr << Lbound << " " << Rbound << " " << flat << " " << stag << endl;
        if (R < Lbound || L > Rbound)
            return this;
        if (L >= Lbound && R <= Rbound)
        {
            ll N = R-L+1;
            ll nEven = N/2;
            ll nOdd = N/2;

            if (N % 2 == 1)
            {
                if (L % 2 == 0)
                    ++nEven;
                else
                    ++nOdd;
            }

            total = (total + flat*N) % Z;

            ll first = ((L-Lbound)*stag) % (10*Z);
            ll last = ((R-Lbound)*stag) % (10*Z);

            total = (total + (first + last)*N/2) % Z;

            if (flat % 2 == 1)
            {
                numOddEven = nEven - numOddEven;
                numOddOdd = nOdd - numOddOdd;
            }

            if (stag % 2 == 1)
            {
                if ((first % 2 == 1 && L % 2 == 1) || (first % 2 == 0 && L % 2 == 0))
                    numOddOdd = nOdd - numOddOdd;
                else
                    numOddEven = nEven - numOddEven;
            }

            upFlat = (upFlat + flat) % Z;
            upStag = (upStag + stag) % Z;
            upFlat = (upFlat + first) % Z;
            return this;
        }

        updateChildren();

        return merge(left->rangeUpdate(Lbound, Rbound, flat, stag), right->rangeUpdate(Lbound, Rbound, flat, stag));
    }

    SegmentNode* emptyRange(ll Lbound, ll Rbound)
    {
        if (R < Lbound || L > Rbound)
            return this;
        if (L >= Lbound && R <= Rbound)
        {
            empty = true;
            total = 0;
            numOddEven = 0;
            numOddOdd = 0;
            upFlat = 0;
            upStag = 0;
            return this;
        }

        updateChildren();
        
        return merge(left->emptyRange(Lbound, Rbound), right->emptyRange(Lbound, Rbound));
    }

    SegmentNode* query(ll LQ, ll RQ)
    {
        if (R < LQ || L > RQ)
            return NULL;
        if (L >= LQ && R <= RQ)
            return this;

        updateChildren();

        return merge(left->query(LQ, RQ), right->query(LQ, RQ));
    }
};

SegmentNode* merge(SegmentNode* left, SegmentNode* right)
{
    if (left == NULL)
        return right;

    if (right == NULL)
        return left;

    return new SegmentNode((left->total + right->total)%Z, (left->numOddEven + 
            right->numOddEven)%Z, (left->numOddOdd + right->numOddOdd)%Z, left->L, right->R, left, right);
}

SegmentNode* build(ll L, ll R, vi &S)
{
    if (L == R)
    {
        bool odd = S[L] % 2;
        if (L % 2 == 0)
            return new SegmentNode(S[L], odd, 0, L, R, NULL, NULL);
        else
            return new SegmentNode(S[L], 0, odd, L, R, NULL, NULL);
    }
    else
    {
        return merge(build(L, (L+R)/2, S), build((L+R)/2+1, R, S));
    }
}

int main()
{
    ll T;
    cin >> T;

    for (ll caseNum = 1; caseNum <= T; ++caseNum)
    {
        ll N, M;
        cin >> N >> M;

        vi S(N), O(M), A(M), B(M), C(M), D(M);
        ll Xs, Ys, Zs;
        ll Xo, Yo, Zo;
        ll Xa, Ya, Za;
        ll Xb, Yb, Zb;
        ll Xc, Yc, Zc;
        ll Xd, Yd, Zd;
        cin >> S[0] >> S[1] >> Xs >> Ys >> Zs;
        cin >> O[0] >> O[1] >> Xo >> Yo >> Zo;
        cin >> A[0] >> A[1] >> Xa >> Ya >> Za;
        cin >> B[0] >> B[1] >> Xb >> Yb >> Zb;
        cin >> C[0] >> C[1] >> Xc >> Yc >> Zc;
        cin >> D[0] >> D[1] >> Xd >> Yd >> Zd;

        for (ll i = 2; i < N; ++i)
        {
            S[i] = (Xs*S[i-2] + Ys*S[i-1] + Zs) % Z;
        }

        for (ll i = 2; i < M; ++i)
        {
            O[i] = (Xo*O[i-2] + Yo*O[i-1] + Zo) % 4 + 1;
            A[i] = (Xa*A[i-2] + Ya*A[i-1] + Za) % N + 1;
            B[i] = (Xb*B[i-2] + Yb*B[i-1] + Zb) % N + 1;
            C[i] = (Xc*C[i-2] + Yc*C[i-1] + Zc) % Z;
            D[i] = (Xd*D[i-2] + Yd*D[i-1] + Zd) % Z;
        }

        for (ll i = 0; i < M; ++i)
            --A[i];

        SegmentNode *root = build(0, N-1, S);

        //for (ll i = 0; i < N; ++i)
        //    cerr << S[i] << endl;

        ll total = 0;
        for (ll i = 0; i < M; ++i)
        {
           // cout << O[i] << " " << A[i] << " " << B[i] << " " << C[i] << " " << D[i] << endl;

            ll L1 = A[i];
            ll R1 = min(A[i]+B[i] -1, N-1);

            ll L2 = 0;
            ll R2 = A[i]+B[i] - N -1;

            SegmentNode *before = root->query(L1, R1);
            before = merge(before, root->query(L2, R2));

            ll beforeTotal = before->total;

            if (O[i] == 1)
            {
                root = root->rangeUpdate(L1, R1, C[i], D[i]);
                root = root->rangeUpdate(L2, R2, C[i] + (N-L1)*D[i], D[i]);

            //    cerr << "before: " << beforeTotal << "after: " << afterTotal << endl;

                ll last = (D[i] * (B[i]-1)) % (10*Z);
                ll added = (C[i]*B[i] + last*B[i]/2) % Z;
                
                SegmentNode *after = root->query(L1, R1);
                after = merge(after, root->query(L2, R2));

                ll readAdded = (after->total - beforeTotal + Z) % Z;

                if (added != readAdded)
                {
                    cerr << "seg tree inconsistency" << endl;
                    cerr << added << " " << readAdded << endl;
                    break;
                }

                total = (total + C[i]*B[i] + last*B[i]/2) % Z;
            }
            else if (O[i] == 2)
            {
                root = root->emptyRange(L1, R1);
                root = root->emptyRange(L2, R2);

                root = root->rangeUpdate(L1, R1, C[i], 0);
                root = root->rangeUpdate(L2, R2, C[i], 0);
                
                /*if ((after->totalEven + after->totalOdd)%Z != (C[i]*B[i])%Z)
                {    
                    cerr << "error in 2 query" << endl;
                }*/

            //    cerr << "beforeTotal: " << beforeTotal << endl;
                total = (total + beforeTotal + C[i]*B[i]) % Z;
            }
            else if (O[i] == 3)
            {
                total = (total + beforeTotal) % Z;
            }
            else
            {
                total = (total + before->numOddOdd + before->numOddEven) % Z;
            }

            //cout << i << ": " <<  total << endl;
        }

        printf("Case #%lld: %lld\n", caseNum, total);
    }
}
