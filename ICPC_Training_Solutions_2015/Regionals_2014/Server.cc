#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n, T;
    for (ll cs = 1; cin >> n >> T; ++cs) {
        vi tasks(n);
        for (ll i = 0; i < n; ++i) {
            cin >> tasks[i];
        }
        
        ll completed = 0;
        for (ll i = 0; i < n; ++i) {
            if (tasks[i] > T)
                break;
            ++completed;
            T -= tasks[i];
        }

        cout << completed << endl;
    }
    return 0;
}
