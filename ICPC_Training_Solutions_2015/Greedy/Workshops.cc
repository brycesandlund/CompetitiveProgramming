#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;

int main() {
    ll w;
    for (ll cs = 1; cin >> w && w; ++cs) {
        vii workshops(w); // (participants, duration)
        for (ll i = 0; i < w; ++i) {
            cin >> workshops[i].first >> workshops[i].second;
        }

        ll r;
        cin >> r;
        vii rooms(r); // (seats, availability)
        for (ll i = 0; i < r; ++i) {
            ll hours, minutes;
            scanf("%lld %lld:%lld", &rooms[i].first, &hours, &minutes);
            rooms[i].second = (hours-14)*60 + minutes;
        }

        sort(workshops.rbegin(), workshops.rend());
        vb available(r, true);
        ll tent_w = 0;
        ll tent_p = 0;
        for (ll i = 0; i < w; ++i) {
            ll best_idx = -1;
            for (ll j = 0; j < r; ++j) {
                if (available[j] && rooms[j].first >= workshops[i].first) {
                    if (rooms[j].second >= workshops[i].second && (best_idx == -1 || rooms[j].second < rooms[best_idx].second)) {
                        best_idx = j;
                    }
                }
            }

            if (best_idx == -1) {
                ++tent_w;
                tent_p += workshops[i].first;
            }
            else {
                available[best_idx] = false;
            }
        }

        printf("Trial %lld: %lld %lld\n\n", cs, tent_w, tent_p);
    }
    return 0;
}
