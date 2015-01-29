#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;


int main()
{
    ll T;
    cin >> T;

    for (ll caseNum = 1; caseNum <= T; ++caseNum)
    {
        ll N, K, P;

        cin >> N >> K >> P;

        ll x = (P*N - 100*K + P*K-1) / (P*K);
        ll curN = N-x*K;

        ll prevN = curN;

        if (P != 100)
        {
            while (curN <= N)
            {
                ll y = (-P*curN + K*P - 100*K +1) / (K*P - 100*K);
                prevN = curN;
                curN += y*K;
            }
        }

        ll ans = (N-prevN)/K + 1;
        printf("Case #%lld: %lld\n", caseNum, max(1LL, ans));
    }
}
