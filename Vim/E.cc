#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<long long>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;

const long long INF = 100000000000000000LL;  // 17 zeros

int get_bit(int x, int pos) { return 1 & (x >> pos); }

int bit_count(int x) {
    int ans = 0;
    for (int i = 0; i < 20; ++i) ans += get_bit(x, i);
    return ans;
}

int main() {
    int n, nenv;
    while (cin >> n >> nenv) {
        vi w(n), h(n), q(n);
        for (int i = 0; i < n; ++i) {
            cin >> w[i] >> h[i] >> q[i];
        }
        
        vvi fit(n, vi(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (w[k] <= w[i] && h[k] <= h[j]) {
                        fit[i][j] |= (1 << k);
                    }
                }
            }
        }
        
        vvvl waste(n, vvl(n, vl(1 << n, 0)));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int x = 0; x < (1 << n); ++x) {
                    for (int k = 0; k < n; ++k) {
                        if (get_bit(x, k) && get_bit(fit[i][j], k)) {
                            waste[i][j][x] += q[k] * (long long) (w[i] * h[j] - w[k] * h[k]);
                        }
                    }
                }
            }
        }
        
        vvi levels(n + 1);
        for (int x = 0; x < (1 << n); ++x) {
            levels[bit_count(x)].push_back(x);
        }
        
        vvl dp(1 << n, vl(nenv + 1, INF));
        dp[0][0] = 0;
        for (int level = 1; level <= n; ++level) {
            for (int x : levels[level]) {
                for (int k = 1; k <= nenv; ++k) {
                    for (int i = 0; i < n; ++i)
                        for (int j = 0; j < n; ++j) {
                            int cards_to_put = fit[i][j] & x;
                            if (cards_to_put == 0) continue;
                            dp[x][k] = min(dp[x][k], dp[x & ~cards_to_put][k - 1] +
                                           waste[i][j][cards_to_put]);
                        }
                }
            }
        }
        cout << dp[(1 << n) - 1][nenv] << endl;
    }
}