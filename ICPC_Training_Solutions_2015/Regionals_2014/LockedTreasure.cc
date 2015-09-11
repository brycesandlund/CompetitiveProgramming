#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

vvi nCr(50, vi(50, 0));

int main() {
    for (ll i = 0; i < 50; ++i) {
        nCr[i][0] = 1;
    }
    
    for (ll i = 1; i < 50; ++i) {
        for (ll j = 1; j <= i; ++j) {
            nCr[i][j] = nCr[i-1][j-1] + nCr[i-1][j];
        }
    }

    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll n, m;
        cin >> n >> m;
        ll keys_per_lock = n-m+1;
        ll n_locks = nCr[n][n-keys_per_lock];
        cout << n_locks << " " << n_locks*keys_per_lock/n << endl;
    }
}
