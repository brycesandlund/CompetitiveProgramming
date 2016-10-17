#include <iostream>
#include <vector>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        string S;
        cin >> S;

        ll n = S.size();
        vvi dp(n, vi(n, INF));
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j <= i; ++j) {
                dp[i][j] = 0;
            }
        }
        for (ll off = 1; off < n; ++off) {
            for (ll i = 0; i+off < n; ++i) {
                ll j = i+off;

                if (S[i] == S[j]) {
                    dp[i][j] = min(dp[i][j], dp[i+1][j-1]);
                }
                dp[i][j] = min(dp[i][j], dp[i+1][j]+1);
                dp[i][j] = min(dp[i][j], dp[i][j-1]+1);
                dp[i][j] = min(dp[i][j], dp[i+1][j-1]+1);
            }
        }

        cout << "Case " << cs << ": " << dp[0][n-1] << endl;
    }
    return 0;
}
