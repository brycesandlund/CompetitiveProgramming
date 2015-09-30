#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int main() {
    ll L, G;
    for (ll cs = 1; cin >> L >> G && L && G; ++cs) {
        vii intervals;
        for (ll i = 0; i < G; ++i) {
            ll xi, ri;
            cin >> xi >> ri;
            intervals.push_back(ii(xi-ri, xi+ri));
        }
        intervals.push_back(ii(L, L));

        sort(intervals.begin(), intervals.end());
        ll last = 0;
        ll best_right = -1;
        ll ints_used = 0;
        bool success = true;
        for (ll i = 0; i < intervals.size(); ++i) {
            if (intervals[i].first > last) {
                if (best_right == -1) {
                    success = false;
                    break;
                }
                if (last >= L)
                    break;
                last = best_right;
                best_right = -1;
                ++ints_used;
                --i;
            }
            else {
                best_right = max(best_right, intervals[i].second);
            }
        }
        if (intervals.back().second < L)
            success = false;

        if (success)
            cout << G - ints_used << endl;
        else
            cout << -1 << endl;
    }
    return 0;
}
