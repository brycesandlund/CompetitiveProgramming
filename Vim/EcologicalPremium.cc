#include <iostream>

using namespace std;

typedef long long ll;

int main()
{
    ll n;
    cin >> n;

    for (size_t caseNum = 1; caseNum <= n; ++caseNum)
    {
        ll f;
        cin >> f;

        ll sum = 0;
        for (size_t i = 0; i < f; ++i)
        {
            ll size, numA, envo;

            cin >> size >> numA >> envo;
            sum += size*envo;
        }

        cout << sum << endl;
    }
}
