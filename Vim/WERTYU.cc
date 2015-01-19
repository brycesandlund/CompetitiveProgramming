#include <iostream>
#include <map>

using namespace std;

typedef long long ll;
typedef map<char, char> mcc;

void add(mcc &qwerty, char arr[], ll len)
{
    for (ll i = 1; i < len; ++i)
    {
        qwerty[arr[i]] = arr[i-1];
    }
}

int main()
{
    mcc qwerty;

    char row1[] = {'`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '='};
    add(qwerty, row1, 13);

    char row2[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\\'};
    add(qwerty, row2, 13);

    char row3[] = {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\''};
    add(qwerty, row3, 11);

    char row4[] = {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/'};
    add(qwerty, row4, 10);

    qwerty[' '] = ' ';

    string line;
    while (getline(cin, line))
    {
        for (ll i = 0; i < line.size(); ++i)
        {
            cout << qwerty[line[i]];
        }

        cout << endl;
    }
}
