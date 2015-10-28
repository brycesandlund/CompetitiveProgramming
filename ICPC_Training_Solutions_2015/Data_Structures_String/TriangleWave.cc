#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        ll amp, freq;
        cin >> amp >> freq;

        for (ll i = 0; i < freq; ++i) {
            if (cs != 1 || i != 0)
                cout << endl;

            for (ll j = 1; j <= amp; ++j) {
                for (ll k = 1; k <= j; ++k)
                    cout << j;

                cout << endl;
            }

            for (ll j = amp-1; j >= 1; --j) {
                for (ll k = 1; k <= j; ++k)
                    cout << j;

                cout << endl;
            }
        }
    }
}
