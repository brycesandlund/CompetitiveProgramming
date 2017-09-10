#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <sstream>
#include <map>
#include <queue>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<double> vd;

int main() {
    cout.precision(18);
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll n;
        cin >> n;
        vi s(n);
        vd p(n);

        for (ll i = 0; i < n; ++i) {
            cin >> s[i] >> p[i];
            p[i] /= 100.0;
        }

        vd best(151, 0);
        best[0] = 1;
        for (ll i = 0; i < n; ++i) {
            for (ll j = 151-s[i]; j >= 0; --j) {
                best[s[i]+j] = max(best[s[i]+j], best[j]*p[i]);
            }
        }

        double ans = 0;
        for (ll i = 76; i < 151; ++i) {
            ans = max(ans, best[i]);
        }

        cout << ans*100 << endl;
    }
}
