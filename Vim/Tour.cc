#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef pair<double, double> dd;
typedef vector<dd> vdd;

    
ll n;

double dist(dd one, dd two) {
    return sqrt(pow(one.first - two.first, 2) + pow(one.second - two.second, 2));
}

double dp(ll p1, ll p2, vvd &d, vvd &memo) {
    ll v = 1 + max(p1, p2);
    if (v == n-1)
        return d[p1][v] + d[v][p2];
    if (memo[p1][p2] > -.5)
        return memo[p1][p2];
    return memo[p1][p2] = min(d[p1][v] + dp(v, p2, d, memo), d[v][p2] + dp(p1, v, d, memo));
}

int main() {
    for (ll cs = 1; cin >> n; ++cs) {
        vdd points(n);
        for (ll i = 0; i < n; ++i) {
            cin >> points[i].first >> points[i].second;
        }

        vvd d(n, vd(n));
        for (ll i = 0; i < n; ++i)
            for (ll j = 0; j < n; ++j)
                d[i][j] = dist(points[i], points[j]);

        vvd memo(n, vd(n, -1));
        printf("%.2lf\n", dp(0, 0, d, memo));
    }
    return 0;
}
