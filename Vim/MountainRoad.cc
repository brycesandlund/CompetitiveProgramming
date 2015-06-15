#include <iostream>
#include <vector>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

int main() {
    ll c;
    cin >> c;
    
    for (ll cs = 1; cs <= c; ++cs) {
        ll n;
        cin >> n;
        
        vi left, right;
        vi t(n), d(n);
        for (ll i = 0; i < n; ++i) {
            char c;
            cin >> ws >> c >> t[i] >> d[i];

            if (c == 'A') {
                left.push_back(i);
            }
            else {
                right.push_back(i);
            }
        }

        vvvi dp(left.size()+1, vvi(right.size()+1, vi(2, INF)));
        vvvi lastStart(left.size()+1, vvi(right.size()+1, vi(2)));

        dp[0][0][0] = 0;
        dp[0][0][1] = 0;

        lastStart[0][0][0] = 0;
        lastStart[0][0][1] = 0;

        for (ll i = 0; i <= left.size(); ++i) {
            for (ll j = 0; j <= right.size(); ++j) {
                if (i > 0) {
                    ll startSame = max(lastStart[i-1][j][0]+10, t[left[i-1]]);
                    ll costSame = max(dp[i-1][j][0]+10, startSame + d[left[i-1]]);

                    ll startDiff = max(dp[i-1][j][1], t[left[i-1]]);
                    ll costDiff = startDiff + d[left[i-1]];

                    if (
                }
                
                for (ll k = 0; k < 2; ++k) {
                    if (i > 0) {
                        if (i > 1) {
                            startLeft[i-1] = max(startLeft[i-1], startLeft[i-2]+10);
                        }

                        ll costSame = max(dp[i-1][j][k]+10, startLeft[i-1] + d[left[i-1]]);
                        dp[i][j][k] = min(dp[i][j][k], costSame);
                        
                        ll costDiff = max(dp[i-1][j][!k], t[left[i-1]]) + d[left[i-1]];
                        dp[i][j][k] = min(dp[i][j][k], costDiff);
                    }
                    if (j > 0) {
                        if (j > 1) {
                            startRight[j-1] = max(startRight[j-1], startRight[j-2]+10);
                        }

                        ll costSame = max(dp[i][j-1][k]+10, startRight[j-1] + d[right[j-1]]);
                        dp[i][j][k] = min(dp[i][j][k], costSame);
                        
                        ll costDiff = max(dp[i][j-1][!k], t[right[j-1]]) + d[right[j-1]];
                        dp[i][j][k] = min(dp[i][j][k], costDiff);
                    }
                }
            }
        }

        ll ans = min(dp[left.size()][right.size()][0], dp[left.size()][right.size()][1]);
        cout << ans << endl;
    }

    return 0;
}
