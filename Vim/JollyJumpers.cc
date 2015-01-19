#include <iostream>
#include <set>

using namespace std;

typedef long long ll;
typedef set<ll> si;

int main()
{
    ll n;
    while (cin >> n)
    {
        ll last;
        cin >> last;
        
        si diffs;
        for (size_t i = 1; i < n; ++i)
        {
            ll cur;
            cin >> cur;

            diffs.insert(abs(cur-last));
            last = cur;
        }

        bool success = true;
        for (size_t i = 1; i <= n-1; ++i)
        {
            if (!diffs.count(i))
                success = false;
        }

        cout << (success ? "Jolly" : "Not jolly") << endl;
    }
}
