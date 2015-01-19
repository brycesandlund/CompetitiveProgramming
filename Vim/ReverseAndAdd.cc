#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

typedef long long ll;

bool palindrome(string &num)
{
    for (ll i = 0; i < num.size()/2; ++i)
    {
        if (num[i] != num[num.size()-i-1])
            return false;
    }

    return true;
}

int main()
{
    ll N;
    cin >> N;

    for (ll caseNum = 1; caseNum <= N; ++caseNum)
    {
        string num;
        cin >> num;

        ll count = 0;
        for (; !palindrome(num); ++count)
        {
            ll numInt = atoi(num.c_str());

            string revNum(num.rbegin(), num.rend());
            ll revNumInt = atoi(revNum.c_str());

            ll sum = numInt + revNumInt;

            stringstream ss;
            ss << sum;
            ss >> num;
        }

        cout << count << " " << num << endl;
    }
}
