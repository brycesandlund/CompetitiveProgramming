#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll N;
        cin >> N;
        
        vi price(N);
        for (ll i = 0; i < N; ++i) {
            cin >> price[i];
        }

        vi max_after(N);
        max_after[N-1] = price[N-1];
        for (ll i = N-2; i >= 0; --i) {
            max_after[i] = max(max_after[i+1], price[i]);
        }

        ll total = 0;
        for (ll i = 0; i < N; ++i) {
            if (price[i] < max_after[i]) {
                total += max_after[i] - price[i];
            }
        }

        cout << total << endl;
    }
}
