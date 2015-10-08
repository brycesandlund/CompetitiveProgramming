#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<bool> vb;
typedef vector<ll> vi;

int main() {
    ll n;
    cin >> n;
    for (ll cs = 1; cs <= n; ++cs) {
        ll m;
        cin >> m;
        vi coins(m);

        ll sum = 0;
        for (ll i = 0; i < m; ++i) {
            cin >> coins[i];
            sum += coins[i];
        }

        vb possible(sum+1, false);
        possible[0] = true;
        for (ll i = 0; i < m; ++i) {
            vb new_possible(possible);
            for (ll j = 0; j < possible.size(); ++j) {
                if (j - coins[i] >= 0) {
                    new_possible[j] = new_possible[j] || possible[j-coins[i]];
                }
            }
            possible = new_possible;
        }

        ll ans = sum;
        for (ll i = sum/2; i >= 0; --i) {
            if (possible[i]) {
                ans = sum-i - i;
                break;
            }
        }
        
        cout << ans << endl;
    }
    return 0;
}
