#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int main() {
    ll n;
    cin >> n;

    vii segments(n);
    for (ll i = 0; i < n; ++i) {
        ll x_i, w_i;
        cin >> x_i >> w_i;

        segments[i] = ii(x_i+w_i, x_i-w_i);
    }

    sort(segments.begin(), segments.end());
    ll clique = 1;
    ll last = segments[0].first;
    for (ll i = 1; i < n; ++i) {
        if (segments[i].second >= last) {
            last = segments[i].first;
            ++clique;
        }
    }

    cout << clique << endl;
}
