#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

vi memo(1000000, -1);

ll f91(ll N)
{
    if (N < 1000000 && memo[N] != -1)
        return memo[N];

    if (N <= 100)
        return memo[N] = f91(f91(N+11));
    else
        return memo[N] = N-10;
}

int main()
{
    for (ll caseNum = 1; true; ++caseNum)
    {
        ll N;
        cin >> N;

        if (N == 0)
            break;

        printf("f91(%lld) = %lld\n", N, f91(N));
    }
}
