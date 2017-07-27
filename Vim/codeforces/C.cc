#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n;
    cin >> n;
    vi a(n);

    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    ll sol = -1;
    for (ll i = n-1; i >= 3; --i) {
        ll others = a[i-1] + a[i-2] + a[i-3];
        if (others > a[i] && !(a[i] == a[i-1] && a[i-2] == a[i-3])) {
            sol = others + a[i];
            break;
        }
    }

    cout << sol << endl;
}
