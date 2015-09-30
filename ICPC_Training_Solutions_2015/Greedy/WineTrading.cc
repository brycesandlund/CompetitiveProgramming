#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n;
    for (ll cs = 1; cin >> n && n; ++cs) {
        vi a(n);
        for (ll i = 0; i < n; ++i) {
            cin >> a[i];
        }

        ll cost = 0;
        ll running = 0;
        for (ll i = 0; i < n; ++i) {
            cost += abs(running);
            running += a[i];
        }

        cout << cost << endl;
    }
    return 0;
}
