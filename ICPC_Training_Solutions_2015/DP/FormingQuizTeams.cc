#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

#define INF 1000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

double d(ii one, ii two) {
    return sqrt(pow(one.first-two.first, 2) + pow(one.second-two.second, 2));
}

int main() {
    ll N;
    for (ll cs = 1; cin >> N && N; ++cs) {
        vii points(2*N);
        for (ll i = 0; i < 2*N; ++i) {
            string name;
            cin >> name >> points[i].first >> points[i].second;
        }

        vvd dist(2*N, vd(2*N));
        for (ll i = 0; i < 2*N; ++i) {
            for (ll j = 0; j < 2*N; ++j) {
                dist[i][j] = d(points[i], points[j]);
            }
        }

        vd cost(1 << (2*N), INF);
        cost[0] = 0;

        for (ll mask = 1; mask < (1 << (2*N)); ++mask) {
            ll set_bits = 0;
            ll first = -1;

            for (ll i = 0; i < 2*N; ++i) {
                if (mask & (1 << i)) {
                    ++set_bits;
                    if (first == -1) {
                        first = i;
                    }
                }
            }

            if (set_bits % 2 == 0) {
                for (ll i = first+1; i < 2*N; ++i) {
                    if (mask & (1 << i)) {
                        ll other = mask & (~(1 << i)) & (~(1 << first));
                        cost[mask] = min(cost[mask], cost[other] + dist[first][i]);
                    }
                }
            }
        }

        printf("Case %lld: %.2lf\n", cs, cost[(1 << (2*N))-1]);
    }
    return 0;
}
