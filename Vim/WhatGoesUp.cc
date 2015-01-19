#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vi::iterator viter;

int main()
{
    vi longest;

    ll num;

    while (cin >> num)
    {
        viter it = upper_bound(longest.begin(), longest.end(), num);

        if (longest.empty())
            longest.push_back(num);
        else if (it == longest.begin())
            *it = num;
        else
        {
            --it;
            if (*it < num)
            {
                ++it;

                if (it == longest.end())
                    longest.push_back(num);
                else
                    *it = num;
            }
        }
    }

    cout << longest.size() << endl;
}
