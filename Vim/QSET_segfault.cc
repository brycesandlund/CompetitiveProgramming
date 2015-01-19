#include <vector>
#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long LL;
typedef vector<LL> vn;

struct SegmentTree;
SegmentTree* merge(SegmentTree* left, SegmentTree* right);

vn combine(vn &one, vn &two)
{
    vn retVal(3, 0);

    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            retVal[(i+j)%3] += one[i] * two[j];

    return retVal;
}

vn add(vn one, vn two)
{
    for (size_t i = 0; i < 3; ++i)
        one[i] += two[i];

    return one;
}

struct SegmentTree
{
    vn leftEnd, rightEnd, whole;
    LL numD3;
    size_t L, R;

    SegmentTree* left;
    SegmentTree* right;

    SegmentTree(vn leftEnd, vn rightEnd, vn whole, LL numD3, size_t L, size_t R, SegmentTree* left, SegmentTree* right) : 
        leftEnd(leftEnd), rightEnd(rightEnd), whole(whole), numD3(numD3), L(L), R(R), left(left), right(right) {}

    SegmentTree* query(size_t LQ, size_t RQ)
    {
        if (R < LQ || L > RQ)
            return NULL;
        if (L >= LQ && R <= RQ)
            return this;

        return merge(left->query(LQ, RQ), right->query(LQ, RQ));
    }

    SegmentTree* update(size_t idx, LL val)
    {
        if (idx < L || idx > R)
            return this;
        if (idx == L && idx == R)
        {
            whole = vn(3, 0);
            whole[val%3]++;
            numD3 = whole[0];
            return this;
        }
        
        return merge(left->update(idx, val), right->update(idx, val));
    }
};

SegmentTree* merge(SegmentTree* left, SegmentTree* right)
{
    if (left == NULL) return right;
    if (right == NULL) return left;

    vn leftEnd = add(left->leftEnd, left->whole);
    leftEnd = add(leftEnd, combine(left->whole, right->leftEnd));

    vn rightEnd = add(right->rightEnd, right->whole);
    rightEnd = add(rightEnd, combine(right->whole, left->rightEnd)); 

    vn whole = combine(left->whole, right->whole);

    LL numD3 = combine(left->rightEnd, right->leftEnd)[0];
    numD3 += combine(left->rightEnd, right->whole)[0];
    numD3 += combine(right->leftEnd, left->whole)[0];
    numD3 += whole[0];
    numD3 += left->numD3 + right->numD3;

    return new SegmentTree(leftEnd, rightEnd, whole, numD3, left->L, right->R, left, right);
}

SegmentTree* build(size_t L, size_t R, vn &A)
{
    if (L == R)
    {
        vn arr(3, 0);
        ++arr[A[L]%3];
        
        return new SegmentTree(vn(3, 0), vn(3, 0), arr, arr[0], L, R, NULL, NULL);
    }
    else
    {
        return merge(build(L, (L+R)/2, A), build((L+R)/2 + 1, R, A));
    }
}

int main()
{
    printf("here");
    LL N, M;
    scanf("%lld %lld", &N, &M);

    string line;

    cin >> line;
    
    vn A(N);
    for (size_t i = 0; i < N; ++i)
    {
        A[i] = line[i] - '0';
    }

    SegmentTree* tree = build(0, N-1, A);

    for (size_t i = 0; i < M; ++i)
    {
        char type;
        scanf("%c", &type);

        if (type == '1')
        {
            size_t X;
            LL Y;

            scanf("%lu %lld", &X, &Y);
            tree = tree->update(X-1, Y);
        }
        else
        {
            size_t C, D;
            
            scanf("%lu %lu", &C, &D);
            SegmentTree* result = tree->query(C-1, D-1);
            printf("%lld\n", result->numD3);
        }
    }
}
