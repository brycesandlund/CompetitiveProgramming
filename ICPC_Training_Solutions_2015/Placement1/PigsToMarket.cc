#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1000000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;


int main() {
    ll n, t;
    for (ll cs = 1; cin >> n >> t; ++cs) {
        vi w(n), diff(n, 0);
        for (ll i = 0; i < n; ++i) {
            cin >> w[i];
        }
        for (ll i = 0; i < n; ++i) {
            ll dist;
            cin >> dist;
            diff[i] -= dist*t;
        }
        for (ll i = 0; i < n; ++i) {
            ll price;
            cin >> price;
            diff[i] += price;
        }

        vi sol(n);
        for (ll i = 0; i < n; ++i) {
            ll town = max_element(diff.begin(), diff.end()) - diff.begin();
            ll pig = max_element(w.begin(), w.end()) - w.begin();
            sol[town] = pig+1;
            diff[town] = -INF;
            w[pig] = -INF;
        }

        cout << sol[0];
        for (ll i = 1; i < n; ++i) {
            cout << " " << sol[i];
        }
        cout << endl;
    }
    return 0;
}
