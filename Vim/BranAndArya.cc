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
    vi a(n);
    for (ll i = 0; i < n; ++i)
        cin >> a[i];

    ll candies = 0;
    ll bran = 0;
    ll ans = -1;
    for (ll i = 0; i < n; ++i) {
        candies += a[i];
        bran += min(candies, 8LL);
        candies -= min(candies, 8LL);
        if (bran >= k) {
            ans = i+1;
            break;
        }
    }

    cout << ans << endl;
}
