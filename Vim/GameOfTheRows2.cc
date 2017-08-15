#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n, k;
    cin >> n >> k;
    vi a(k);
    for (ll i = 0; i < k; ++i) {
        cin >> a[i];
    }

    ll singles = 0;
    ll quads = 0;
    ll doubles = 0;
    for (ll i = 0; i < k; ++i) {
        quads += a[i] / 4;
        a[i] -= (a[i] / 4)*4;
        if (a[i] >= 2) {
            ++doubles;
            a[i] -= 2;
        }
        if (a[i] == 1)
            ++singles;
    }

    if (quads > n) {
        doubles += (quads - n) * 2;
    }

    if (quads < n) {
        ll remaining = n-quads;
        if (doubles >= remaining) {
            doubles -= remaining;
            singles = max(0LL, singles-remaining);
        }
        else {
            singles = max(0LL, singles - doubles);
            remaining -= doubles;
            singles = max(0LL, singles-remaining*2);
            doubles = 0;
        }
    }

    if (doubles + singles <= n*2) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}
