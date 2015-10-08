#include <iostream>
#include <vector>

#define INF 1000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

ll solve(ll k, ll lb, ll ub, vvvi &memo) {
    if (lb+1 == ub) return 0;

    if (memo[k][lb][ub] != -1)
        return memo[k][lb][ub];

    if (k == 1) return (lb+1+ub-1) * (ub-lb-1) / 2;
    
    ll best = INF;
    for (ll i = lb+1; i < ub; ++i) {
        best = min(best, max(solve(k-1, lb, i, memo), solve(k, i, ub, memo))+i);
    }
    return memo[k][lb][ub] = best;
}

int main() {
    ll N;
    cin >> N;
    vvvi memo(11, vvi(102, vi(102, -1)));
    
    for (ll cs = 1; cs <= N; ++cs) {
        ll k, m;
        cin >> k >> m;

        cout << solve(k, 0, m+1, memo) << endl;
    }
    return 0;
}
