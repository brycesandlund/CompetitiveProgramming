#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

#define EP 1e-10
#define N 100000010

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main()
{
    ll T;
    cin >> T;

    vi sieve(N, 0);
    
    for (ll i = 2; i <= sqrt(N)+EP; ++i)
        if (sieve[i] == 0)
            for (ll j = i; j <= N; j += i)
                ++sieve[j];

    for (ll caseNum = 1; caseNum <= T; ++caseNum)
    {
        ll A, B, K;
        cin >> A >> B >> K;

        ll count = 0;
        for (ll i = A; i <= B; ++i)
        {
            if (sieve[i] == K)
                ++count;
        }

        printf("Case #%lld: %lld\n", caseNum, count);
    }
}
