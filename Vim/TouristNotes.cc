#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

int main() {
    ll n, m;
    cin >> n >> m;

    ll prev_di, prev_hdi;
    cin >> prev_di >> prev_hdi;
    
    bool success = true;
    ll maxH = prev_hdi + prev_di - 1;

    if (m == 1) {
        maxH = max(maxH, n-prev_di + prev_hdi);
    }

    for (ll i = 1; i < m; ++i) {
        ll di, hdi;
        cin >> di >> hdi;

        ll h_delta = abs(hdi - prev_hdi);
        ll d_delta = di - prev_di;
        if (h_delta > d_delta) {
            success = false;
            break;
        }
        else {
            ll curMaxH = (d_delta - h_delta) / 2 + max(prev_hdi, hdi);
            maxH = max(maxH, curMaxH);
        }

        if (i == m-1) {
            maxH = max(maxH, n-di + hdi);
        }

        prev_hdi = hdi;
        prev_di = di;
    }

    if (success)
        cout << maxH << endl;
    else
        cout << "IMPOSSIBLE" << endl;

    return 0;
}
