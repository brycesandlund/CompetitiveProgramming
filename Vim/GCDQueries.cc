#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

typedef vector<size_t> VI;
typedef vector<VI> VVI;
typedef long long LL;

// basic gcd
LL gcd( LL a, LL b ) {
	if( a < 0 ) return gcd(-a,b);
	if( b < 0 ) return gcd(a,-b);
	LL c;
	while( b ) { c = a % b; a = b; b = c; }
	return a;
}

LL gcdRange(int start, int end, VVI &memo)
{
    if (start > end)
        return 0;

    size_t d = (size_t)(log(end - start+1) / log(2));
    size_t rounded = (size_t)pow(2, d)-1;
    return gcd(memo[d][start], memo[d][end-rounded]);
}

int main()
{
    size_t T;
    scanf("%lu", &T);

    for (size_t caseNum = 1; caseNum <= T; ++caseNum)
    {
        size_t N, Q;
        scanf("%lu %lu", &N, &Q);

        VI A(N);

        for (size_t i = 0; i < N; ++i)
        {
            scanf("%lu", &A[i]);
        }

        VVI memo;
        memo.push_back(A);

        for (size_t shift = 1; shift < N; shift <<= 1)
        {
            VI cur(N, 0);
            
            for (size_t j = 0; j < N-shift; ++j)
            {
                cur[j] = gcd(memo.back()[j], memo.back()[j+shift]);
            }

            memo.push_back(cur);
        }

        for (size_t i = 0; i < Q; ++i)
        {
            int L, R;
            scanf("%d %d", &L, &R);

            size_t ans = gcd(gcdRange(0, L-2, memo), gcdRange(R, N-1, memo));
            printf("%lu\n", ans);
        }
    }
}
