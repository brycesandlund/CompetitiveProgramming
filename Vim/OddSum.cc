#include <iostream>

using namespace std;

typedef long long ll;

int main()
{
    ll T;
    cin >> T;

    for (ll caseNum = 1; caseNum <= T; ++caseNum)
    {
        ll a, b;
        cin >> a >> b;

        if (a % 2 == 0)
            ++a;
        if (b % 2 == 0)
            --b;

        ll sum = ((b-a+2)*(a+b))/4;
        printf("Case %lld: %lld\n", caseNum, sum);
    }
}
