#include <iostream>
#include <sstream>

using namespace std;

typedef long long ll;

int main()
{
    for (ll caseNum = 1; true; ++caseNum)
    {
        ll N;
        cin >> N;

        if (N < 0)
            break;

        if (N == 0)
            cout << 0 << endl;
        else
        {
            string tern = "";
            while (N != 0)
            {
                ll digit = N % 3;
                stringstream temp;
                string digitStr;
                temp << digit;
                temp >> digitStr;

                tern = digitStr + tern;
                N /= 3;
            }

            cout << tern << endl;
        }
    }
}
