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

    vii gain, loss;

    for (ll i = 0; i < n; ++i) {
        ll a, b;
        cin >> a >> b;
        if (b >= a) {
            gain.push_back(ii(a, b));
        }
        else {
            loss.push_back(ii(b, a));
        }
    }

    sort(loss.rbegin(), loss.rend());
    sort(gain.begin(), gain.end());

    ll surplus = 0;
    ll needed = 0;
    for (ll i = 0; i < gain.size(); ++i) {
        if (gain[i].first > surplus) {
            needed += gain[i].first - surplus;
            surplus = gain[i].first;
        }
        surplus += gain[i].second - gain[i].first;
    }

    for (ll i = 0; i < loss.size(); ++i) {
        if (loss[i].second > surplus) {
            needed += loss[i].second - surplus;
            surplus = loss[i].second;
        }
        surplus += loss[i].first - loss[i].second;
    }
    cout << needed << endl;
    return 0;
}
