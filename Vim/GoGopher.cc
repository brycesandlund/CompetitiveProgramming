#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;
typedef vector<vb> vvb;

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll A;
        cin >> A;
        vvb grid(3, vb(1000, false));
        for (ll i = 0; true/*i < (A+8)/9*/;) {
            cout << 2 << " " << 2+i*3 << endl;
            cout.flush();

            ll x, y;
            cin >> x >> y;

            if (x == 0 && y == 0)
                break;

            --x;
            --y;
            grid[x][y] = true;

            bool filled = true;
            for (ll j = 0; j <= 2; ++j) {
                for (ll k = i*3; k <= i*3+2; ++k) {
                    if (!grid[j][k]) {
                        filled = false;
                    }
                }
            }

            if (filled)
                ++i;
        }
    }
}
