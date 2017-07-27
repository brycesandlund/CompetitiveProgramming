#include <iostream>
#include <vector>
#include <cstring>

#define M 1024523

using namespace std;

typedef int ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

string pipe_l, pipe_r;
ll n, m;
ll memo[501][501][501];

ll solve(ll l1, ll r1, ll l2, ll r2) {
    if (l1 == n && r1 == m && l2 == n && r2 == m)
        return 1;

    if (memo[l1][r1][l2] != -1)
        return memo[l1][r1][l2];

    ll ans = 0;
    if (l1 < n && l2 < n && pipe_l[l1] == pipe_l[l2])
        ans += solve(l1+1, r1, l2+1, r2);
    if (l1 < n && r2 < m && pipe_l[l1] == pipe_r[r2])
        ans += solve(l1+1, r1, l2, r2+1);
    if (r1 < m && l2 < n && pipe_r[r1] == pipe_l[l2])
        ans += solve(l1, r1+1, l2+1, r2);
    if (r1 < m && r2 < m && pipe_r[r1] == pipe_r[r2])
        ans += solve(l1, r1+1, l2, r2+1);

    ans = ans % M;
    return memo[l1][r1][l2] = ans;
}

int main() {
    cin >> n >> m >> pipe_l >> pipe_r;
    memset(memo, -1, sizeof(memo));
    cout << solve(0, 0, 0, 0) << endl;
}
