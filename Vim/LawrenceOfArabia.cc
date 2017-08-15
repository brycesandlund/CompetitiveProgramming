#include <iostream>
#include <vector>

#define INF 100000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll n, m;
    for (ll cs = 1; cin >> n >> m && n; ++cs) {
        vi SV(n);
        for (ll i = 0; i < n; ++i)
            cin >> SV[i];

        vvi cost(n, vi(n, 0));
        vvi sum(n, vi(n, 0));
        for (ll i = 0; i < n; ++i)
            sum[i][i] = SV[i];

        for (ll i = 1; i < n; ++i) {
            for (ll j = 0; i+j < n; ++j) {
                cost[j][i+j] = cost[j][i+j-1] + sum[j][i+j-1]*SV[i+j];
                sum[j][i+j] = sum[j][i+j-1] + SV[i+j];
            }
        }

        vvi dp(m+1, vi(n, INF));
        for (ll i = 0; i < n; ++i)
            dp[0][i] = cost[0][i];

        vvi opt(m+1, vi(n));
        for (ll i = 0; i <= m; ++i) {
            opt[i][0] = 0;
            dp[i][0] = 0;
        }

        ll C = 6;
        for (ll i = 1; i <= m; ++i) {
            for (ll j = 1; j < n; ++j) {
                for (ll k = opt[i][j-1]; k < min(opt[i][j-1]+C, j); ++k) {
                    ll value = dp[i-1][k] + cost[k+1][j];
                    if (value <= dp[i][j]) {
                        opt[i][j] = k;
                        dp[i][j] = value;
                    }
                }
            }
        }

        cout << dp[m][n-1] << endl;
    }
}
