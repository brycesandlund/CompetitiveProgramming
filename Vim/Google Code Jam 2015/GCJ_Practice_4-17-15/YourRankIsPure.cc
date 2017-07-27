#include <iostream>
#include <vector>

#define M 100003
#define N 510

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

vvi nCr(N, vi(N, 0));

void fill_nCr() {
    for (ll i = 0; i < N; ++i) {
        nCr[i][0] = 1;
    }

    for (ll i = 1; i < N; ++i) {
        for (ll j = 1; j <= i; ++j) {
            nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j])%M;
        }
    }
}

ll waysToFill(ll upper, ll lower, ll spaces) {
    return nCr[upper-lower-1][spaces];
}

int main() {
    fill_nCr();

    vvi dp(N, vi(N, 0));
    for (ll i = 2; i < N; ++i) {
        dp[i][1] = 1;

        for (ll j = 2; j < i; ++j) {
            for (ll k = j-1; k >= 1; --k) {
                dp[i][j] = (dp[i][j] + dp[j][k]*waysToFill(i, j, j-k-1)) % M;
            }
        }
    }

    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        ll n;
        cin >> n;

        ll total = 0;
        for (ll j = 1; j < n; ++j) {
            total = (total + dp[n][j]) % M;
        }

        printf("Case #%lld: %lld\n", cs, total);
    }

    return 0;
}
