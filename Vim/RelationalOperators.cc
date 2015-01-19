#include <iostream>

using namespace std;

typedef long long ll;

int main()
{
    ll t;
    cin >> t;

    for (size_t i = 0; i < t; ++i)
    {
        ll a, b;
        cin >> a >> b;

        if (a < b)
            cout << '<' << endl;
        else if (a > b)
            cout << '>' << endl;
        else
            cout << '=' << endl;
    }
}
