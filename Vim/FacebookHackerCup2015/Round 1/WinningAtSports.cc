#include <iostream>
#include <cstdio>
#include <vector>

#define M 1000000007LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main()
{
    ll T;
    cin >> T;

    for (ll caseNum = 1; caseNum <= T; ++caseNum)
    {
        ll me, you;
        scanf("%lld-%lld", &me, &you);

        vvi stressFree(me+1, vi(you+1, 0));

        for (ll i = 1; i <= me; ++i)
            stressFree[i][0] = 1;

        for (ll i = 1; i <= me; ++i)
        {
            for (ll j = 1; j <= you; ++j)
            {
                if (i > j)
                {
                    stressFree[i][j] = (stressFree[i-1][j] + stressFree[i][j-1])%M;
                }    
            }
        }

        vvi stressful(me+1, vi(you+1, 0));

        for (ll j = 0; j <= you; ++j)
            stressful[0][j] = 1;

        for (ll i = 1; i <= me; ++i)
        {
            for (ll j = 1; j <= you; ++j)
            {
                if (j >= i || j == you)
                {
                    stressful[i][j] = (stressful[i-1][j] + stressful[i][j-1])%M;
                }
            }
        }

        printf("Case #%lld: %lld %lld\n", caseNum, stressFree[me][you], stressful[me][you]);
    }
}
