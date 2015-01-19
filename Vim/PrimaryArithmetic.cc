#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

typedef long long ll;

int main()
{
    string one, two;

    while (true)
    {
        cin >> one >> two;

        if (one == "0" && two == "0")
            break;

        ll count = 0;
        bool carry = false;
        for (ll i1 = one.size()-1, i2 = two.size()-1; i1 >= 0 || i2 >= 0; --i1, --i2)
        {
            ll d1 = i1 >= 0 ? (one[i1] - '0') : 0;
            ll d2 = i2 >= 0 ? (two[i2] - '0') : 0;

            ll sum = d1 + d2 + carry;
            if (sum >= 10)
            {
                ++count;
                carry = true;
            }
            else
                carry = false;
        }

        if (count == 0)
            cout << "No";
        else
            cout << count;

        cout << " carry operation" << (count > 1 ? "s" : "") << "." << endl;
    }
}
