#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll timeToDuration(ll hour, ll minute) {
    return (hour-14)*60 + minute;
}

int main() {
    for (ll cs = 1; true; ++cs) {
        ll w;
        cin >> w;

        if (w == 0) break;

        vii workshops(w);
        for (ll i = 0; i < w; ++i) {
            cin >> workshops[i].first >> workshops[i].second;
        }

        ll r;
        cin >> r;
        vii rooms(r);
        for (ll i = 0; i < r; ++i) {
            cin >> rooms[i].first;
            ll hour, minute;
            scanf("%lld:%lld", &hour, &minute);
            rooms[i].second = timeToDuration(hour, minute);
        }

        sort(workshops.begin(), workshops.end());
        ll matched = 0;
        ll people = 0;
        for (ll i = w-1; i >= 0; --i) {
            ll bestIdx = -1;
            for (ll j = 0; j < rooms.size(); ++j) {
                if (rooms[j].first >= workshops[i].first && rooms[j].second >= workshops[i].second) {
                    if (bestIdx == -1 || rooms[j].second < rooms[bestIdx].second) {
                        bestIdx = j;
                    }
                }
            }

            if (bestIdx != -1) {
                ++matched;
                people += workshops[i].first;
                rooms.erase(rooms.begin()+bestIdx);
            }
        }

        ll totalPeople = 0;
        for (ll i = 0; i < w; ++i) {
            totalPeople += workshops[i].first;
        }

        printf("Trial %lld: %lld %lld\n\n", cs, w-matched, totalPeople-people);
    }
}
