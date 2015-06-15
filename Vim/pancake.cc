#include <iostream>
#include <cstdio>
#include <vector>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        ll D;
        cin >> D;
        vi P(D);
        for (ll i = 0; i < D; ++i) {
            cin >> P[i];
        }

        ll ans = INF;
        for (ll x = 1; x < 1010; ++x) {
            ll cur = 0;
            for (ll i = 0; i < D; ++i) {
                if (P[i] > x) {
                    cur += (P[i]+x-1) / x - 1;
                }
            }

            ans = min(ans, x + cur);
        }

        printf("Case #%lld: %lld\n", cs, ans);
    }
}
