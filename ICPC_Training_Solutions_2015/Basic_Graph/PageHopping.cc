#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

#define INF 100000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    for (ll cs = 1; true; ++cs) {
        vvi adjMatrix(100, vi(100, INF));

        while (true) {
            ll a, b;
            cin >> a >> b;
            if (a == 0 && b == 0)
                break;
            --a;
            --b;
            adjMatrix[a][b] = 1;
            adjMatrix[a][a] = 0;
            adjMatrix[b][b] = 0;
        }

        for (ll k = 0; k < 100; ++k) {
            for (ll i = 0; i < 100; ++i) {
                for (ll j = 0; j < 100; ++j) {
                    ll new_cost = adjMatrix[i][k] + adjMatrix[k][j];
                    adjMatrix[i][j] = min(adjMatrix[i][j], new_cost);
                }
            }
        }

        ll total_dist = 0;
        ll active_sqr = 0;
        for (ll i = 0; i < 100; ++i) {
            for (ll j = 0; j < 100; ++j) {
                if (i == j)
                    continue;
                if (adjMatrix[i][j] != INF) {
                    total_dist += adjMatrix[i][j];
                    ++active_sqr;
                }
            }
        }

        if (total_dist == 0)
            break;

        printf("Case %lld: average length between pages = %.3lf clicks\n", cs, (double)total_dist/active_sqr);
    }
    return 0;
}
