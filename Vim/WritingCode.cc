#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

int main() {
    ll n, m, b, mod;
    cin >> n >> m >> b >> mod;

    vi a(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vvi ways(b+1, vi(n, 0));
    for (ll i = 0; i < n; ++i) {
        ways[0][i] = 1;
    }

    for (ll i = 1; i <= m; ++i) {
        vvi new_ways(b+1, vi(n, 0));

        for (ll j = 0; j <= b; ++j) {
            for (ll k = 0; k < n; ++k) {
                if (j - a[k] >= 0) {
                    new_ways[j][k] = ways[j-a[k]][k];
                }

                if (k > 0) {
                    new_ways[j][k] = (new_ways[j][k] + new_ways[j][k-1]) % mod;
                }

                //cerr << j << ", " << k << " " << new_ways[j][k] << endl;
            }
        }

        ways = new_ways;
    }

    ll ans = 0;
    for (ll j = 0; j <= b; ++j) {
        ans = (ans + ways[j][n-1]) % mod;
    }

    cout << ans << endl;
}
