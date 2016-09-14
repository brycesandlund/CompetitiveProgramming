#include <iostream>
#include <vector>
#include <cmath>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

ll cuberoot(ll n) {
    double root = pow(n, 1.0/3);
    return (ll)(root + EP);
}

ii best;

void rec(ll m, ll steps, ll subtracted) {
    if (m == 0) {
        best = max(best, ii(steps, subtracted));
        return;
    }
    ll x = cuberoot(m);
    rec(m - x*x*x, steps+1, subtracted + x*x*x);
    if (x-1 >= 0) {
        rec(x*x*x-1 - (x-1)*(x-1)*(x-1), steps+1, subtracted + (x-1)*(x-1)*(x-1));
    }
}

int main() {
    ll m;
    cin >> m;
    rec(m, 0, 0);
    cout << best.first << " " << best.second << endl;
    return 0;
}
