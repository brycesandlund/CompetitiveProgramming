#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

vi cycles(1000010, -1);

ll solve(ll num)
{
    if (num <= 1000000 && cycles[num] != -1)
        return cycles[num];

    if (num == 1)
        return 1;

    ll nextNum;
    if (num % 2 == 0)
        nextNum = num/2;
    else
        nextNum = num*3 + 1;

    ll ans = solve(nextNum)+1;
    if (num <= 1000000)
        cycles[num] = ans;

    return ans;
}

int main()
{
    size_t i, j;
    while (cin >> i >> j)
    {
        ll maxN = -1;
        for (size_t k = min(i, j); k <= max(i, j); ++k)
            maxN = max(maxN, solve(k));

        printf("%lu %lu %lld\n", i, j, maxN);
    }
}
