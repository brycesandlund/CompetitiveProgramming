#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define _USER_MATH_DEFINES
#include <cmath>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<double> vd;

void adjust(vd &angles, ll &pointer1, ll &pointer2, double &angle2) {
    double angle1 = angles[pointer1];

    while (angle2 < angle1 + M_PI - EP) {
        //cerr << pointer1 << " " << pointer2 << endl;
        //cerr << angle1 << " " << angle2 << endl;
        ++pointer2;
        if (pointer2 == angles.size()) {
            angle2 += angles[0] - angles.back() + 2*M_PI;
            pointer2 = 0;
        }
        else {
            angle2 += angles[pointer2] - angles[pointer2-1];
        }
    }
}

int main() {
    ll T;
    cin >> T;
    
    for (ll cs = 1; cs <= T; ++cs) {
        ll N;
        cin >> N;

        vii trees(N);
        for (ll i = 0; i < N; ++i) {
            cin >> trees[i].first >> trees[i].second;
        }

        printf("Case #%lld:\n", cs);

        for (ll i = 0; i < N; ++i) {
            vd angles;
            for (ll j = 0; j < N; ++j) {
                if (i == j) continue;

                ii ptTranslate(trees[j].first - trees[i].first, trees[j].second - trees[i].second);
                angles.push_back(atan2(ptTranslate.second, ptTranslate.first));
            }

            sort(angles.begin(), angles.end());

            for (ll k = 0; k < angles.size(); ++k) {
        //        cerr << angles[k] << endl;
            }

            ll pointer1 = 0;
            ll pointer2 = 1;
            double angle2 = angles[pointer2];

            ll minCuts = N;
            for (; pointer1 < angles.size(); ++pointer1) {
                adjust(angles, pointer1, pointer2, angle2);
                ll diff;
                if (pointer2 > pointer1) {
                    diff = pointer2 - pointer1 - 1;
                }
                else {
                    diff = angles.size() - pointer1 - 1 + pointer2;
                }

                minCuts = min(minCuts, diff);
            }

            if (N <= 2) {
                cout << 0 << endl;
            }
            else {
                cout << minCuts << endl;
            }
        }

    }

    return 0;
}
