#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

int main()
{
    char c;
    bool start = true;
    while (cin >> noskipws >> c)
    {
        if (c == '"')
        {
            if (start)
                cout << '`' << '`';
            else
                cout << '\'' << '\'';

            start = !start;
        }
        else
            cout << c;
    }
}
