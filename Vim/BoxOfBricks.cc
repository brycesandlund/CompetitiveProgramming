#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main()
{
    for (ll caseNum = 1; true; ++caseNum)
    {
        ll n;
        cin >> n;

        if (n == 0)
            break;

        vi h(n);

        ll sum = 0;
        for (ll i = 0; i < n; ++i)
        {
            cin >> h[i];
            sum += h[i];
        }

        ll stackSize = sum/n;

        ll count = 0;

        for (ll i = 0; i < n; ++i)
        {
            count += max(0LL, h[i]-stackSize);
        }

        printf("Set #%lld\n", caseNum);
        printf("The minimum number of moves is %lld.\n\n", count);
    }
}
