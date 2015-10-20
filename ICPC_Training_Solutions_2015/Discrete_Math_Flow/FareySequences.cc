#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef pair<double, ii> dii;
typedef vector<dii> vdii;

ll gcd(ll a, ll b) {
    if (a < 0) return gcd(-1, b);
    if (b < 0) return gcd(a, -b);
    ll c;
    while (b) { c = a % b; a = b; b = c; }
    return a;
}

int main() {
    ll n, k;
    for (ll cs = 1; cin >> n >> k; ++cs) {
        vdii farey;
        for (ll i = 1; i <= n; ++i) {
            for (ll j = i; j <= n; ++j) {
                if (gcd(i, j) == 1) {
                    farey.push_back(dii(((double)i)/j, ii(i, j)));
                }
            }
        }

        sort(farey.begin(), farey.end());

        printf("%lld/%lld\n", farey[k-1].second.first, farey[k-1].second.second);
    }
    return 0;
}
