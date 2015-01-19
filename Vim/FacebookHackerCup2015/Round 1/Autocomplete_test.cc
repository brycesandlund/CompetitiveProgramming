#include <iostream>

using namespace std;

typedef long long ll;

int main()
{
    cout << 1 << endl;
    cout << 1 << endl;

    for (ll i = 0; i < 1000000; ++i)
    {
        cout << (char)(rand()%26 + 'a');
    }

    cout << endl;
}
