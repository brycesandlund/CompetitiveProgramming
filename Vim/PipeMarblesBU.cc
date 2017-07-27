#include <iostream>
#include <vector>

#define M 1024523

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

string pipe_l, pipe_r;
ll n, m;

int main() {
    cin >> n >> m >> pipe_l >> pipe_r;
    vvvi dp(n+1, vvi(m+1, vi(n+1, 0)));

    dp[n][m][n] = 1;
    for (ll l1 = n; l1 >= 0; --l1) {
        for (ll r1 = m; r1 >= 0; --r1) {
            for (ll l2 = n; l2 >= 0; --l2) {
                ll r2 = l1+r1 - l2;
                if (r2 < 0 || r2 > m)
                    continue;

                if (l1 < n && l2 < n && pipe_l[l1] == pipe_l[l2])
                    dp[l1][r1][l2] += dp[l1+1][r1][l2+1];
                if (l1 < n && r2 < m && pipe_l[l1] == pipe_r[r2])
                    dp[l1][r1][l2] += dp[l1+1][r1][l2];
                if (r1 < m && l2 < n && pipe_r[r1] == pipe_l[l2])
                    dp[l1][r1][l2] += dp[l1][r1+1][l2+1];
                if (r1 < m && r2 < m && pipe_r[r1] == pipe_r[r2])
                    dp[l1][r1][l2] += dp[l1][r1+1][l2];

                dp[l1][r1][l2] %= M;
            }
        }
    }

    cout << dp[0][0][0] << endl;
}
