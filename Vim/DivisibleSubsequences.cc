#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll c;
    cin >> c;

    for (ll cs = 1; cs <= c; ++cs) {
        ll d, n;
        cin >> d >> n;

        vi nums(n);
        for (ll i = 0; i < n; ++i) {
            cin >> nums[i];
        }

        ll sum = 0;
        vi modulo(d, 0);
        modulo[0] = 1;
        ll total = 0;
        for (ll i = 0; i < n; ++i) {
            sum = (sum + nums[i]) % d;
            total += modulo[sum];
            ++modulo[sum];
        }

        cout << total << endl;
    }
    return 0;
}
