#include <iostream>
#include <vector>
#include <algorithm>

#define INF 100000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll m, h1, a1, x1, y1, h2, a2, x2, y2;
    cin >> m >> h1 >> a1 >> x1 >> y1 >> h2 >> a2 >> x2 >> y2;

    ll ans = -1;
    for (ll i = 1; i <= m; ++i) {
        h1 = (h1 * x1 + y1) % m;
        h2 = (h2 * x2 + y2) % m;

        if (h1 == a1 && h2 == a2) {
            ans = i;
            break;
        }
    }

    cout << ans << endl;

    return 0;
}
