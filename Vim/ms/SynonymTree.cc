#include <iostream>
#include <vector>

#define M 1000000007

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll powmod(ll a, ll b) {
    if (b == 0) return 1;
    if (b == 1) return a % M;
    ll t = powmod(a, b/2);
    t = (t*t)%M;
    if (b % 2) t = (t*a)%M;
    return t >= 0 ? t : t + M;
}

int main() {
    ll N;
    for (ll cs = 1; cin >> N; ++cs) {
        vi d(N);
        for (ll i = 0; i < N; ++i) {
            cin >> d[i];
        }

        ll ans = 1;
        ll total = 0;
        for (ll i = 0; i < N; ++i) {
            total = (total + d[i]);
            if (i > 0) {
            //    ans = (ans * powmod(2, (total-1)*d[i])) % M;
                ans = (ans * powmod(powmod(2, (total-1)), d[i])) % M;
            }
            if (i < N-1) {
                ans = (ans * powmod(powmod(2, d[i]) - 1, d[i+1])) % M;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
