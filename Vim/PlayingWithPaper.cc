#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    ll a, b;
    cin >> a >> b;
    ll count = 0;
    while (true) {
        if (a < b)
            swap(a, b);

        if (b == 0)
            break;

        ll squares = a / b;
        count += squares;
        a = a - squares*b;
    }

    cout << count << endl;

    return 0;
}
