#include <iostream>
#include <vector>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll n, m;
    for (ll cs = 1; cin >> n >> m; ++cs) {
        vvi adj_matrix(n, vi(n, INF));

        for (ll i = 0; i < m; ++i) {
            ll u, v, t;
            cin >> u >> v >> t;
            adj_matrix[u][v] = t;
            adj_matrix[v][u
        }
    }
    return 0;
}
