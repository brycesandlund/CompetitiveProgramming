#include <iostream>
#include <vector>
#include <cstdio>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll cross(ii &pt1, ii &pt2) {
    return pt1.first*pt2.second - pt1.second*pt2.first;
}

double ComputeSignedArea(vii &p) {
    double area = 0;
    for (ll i = 0; i < p.size(); ++i) {
        ll z = (i+1) % p.size();
        area += cross(p[i], p[z]);
    }
    return area / 2;
}

int main() {
    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        ll N;
        cin >> N;

        vii points(N);
        for (ll i = 0; i < N; ++i) {
            cin >> points[i].first >> points[i].second;
        }

        ll W;
        cin >> W;

        double volume = ComputeSignedArea(points)*W;

        double initp, spent, add;
        cin >> initp >> spent >> add;
        initp *= .01;

        double initv = initp*volume;
        double afterconsume = initv - spent;
        if (afterconsume <= -EP) {
            printf("Lack of water. ");
            afterconsume = 0;
        }

        double afterrain = afterconsume+add;
        if (afterrain - EP >= volume) {
            printf("Excess of water. ");
            afterrain = volume;
        }

        ll finalp = (ll)(afterrain/volume * 100);
        printf("Final percentage: %lld%%\n", finalp);
    }
    return 0;
}
