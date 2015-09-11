#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
    
vvi nCr(50, vi(50, 0));

ll multi_choose(ll n, ll r) {
    ll k = n+r-1;
    if (r > k || r < 0 || k < 0)
        return 0;
    return nCr[k][r];
}

int main() {
    for (ll i = 0; i < 50; ++i) {
        nCr[i][0] = 1;
    }
    
    for (ll i = 1; i < 50; ++i) {
        for (ll j = 1; j <= i; ++j) {
            nCr[i][j] = nCr[i-1][j-1] + nCr[i-1][j];
        }
    }

    ll n;
    for (ll cs = 1; cin >> n && n; ++cs) {
        vi ratings(n);
        ll sum = 0;
        for (ll i = 0; i < n; ++i) {
            cin >> ratings[i];
            sum += ratings[i];
        }

        ll ways = 0;
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < ratings[i]; ++j) {
                ways += multi_choose(sum-j+1, n-i-1);
            }
            for (ll j = ratings[i]+1; j < sum; ++j) {
                ways += multi_choose(sum-j, n-i-1);
            }
            sum -= ratings[i];
        }

        cout << ways+1 << endl;
    }
    return 0;
}
