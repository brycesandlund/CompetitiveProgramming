#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll N;
        cin >> N;

        vi W(N);
        for (ll i = 0; i < N; ++i) {
            cin >> W[i];
        }

        sort(W.begin(), W.end());
        ll b_ptr = N-1;
        ll f_ptr = 0;
        ll trips = 0;
        while (true) {
            ll weight = W[b_ptr];
            while (weight < 50 && f_ptr < b_ptr) {
                weight += W[b_ptr];
                ++f_ptr;
            }

            if (weight >= 50) {
                ++trips;
            }
            if (f_ptr == b_ptr)
                break;
            else
                --b_ptr;
        }

        printf("Case #%lld: %lld\n", cs, trips);
    }
}
