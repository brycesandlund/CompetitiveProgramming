#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll n, m, b, mod;
    cin >> n >> m >> b >> mod;

    vi a(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vvi ways(m+1, vi(b+1, 0));
    ways[0][0] = 1;

    for (ll i = 1; i <= m; ++i) {
        for (ll j = 0; j <= b; ++j) {
            for (ll k = 0; k < n; ++k) {
                if (j - a[k] >= 0) {
                    ways[i][j] = (ways[i][j] + ways[i-1][j-a[k]]) % mod;
                }
            }
        }
    }

    ll ans = 0;
    for (ll j = 0; j <= b; ++j) {
        ans = (ans + ways[m][j]) % mod;
    }

    cout << ans << endl;
}
