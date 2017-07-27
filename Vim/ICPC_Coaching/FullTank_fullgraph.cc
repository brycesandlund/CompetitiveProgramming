#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<ll> vi;
typedef vector<vi> vvi;

typedef pair<ll, ii> iii;
typedef vector<iii> viii;
typedef vector<viii> vviii;
typedef vector<vviii> vvviii;

int main() {
    ll n, m;
    for (ll cs = 1; cin >> n >> m; ++cs) {
        vi p(n);
        for (ll i = 0; i < n; ++i) {
            cin >> p[i];
        }

        vvii baseGraph(n);

        for (ll i = 0; i < m; ++i) {
            ll u, v, d;
            cin >> u >> v >> d;
            
            baseGraph[u].push_back(ii(v, d));
            baseGraph[v].push_back(ii(u, d));
        }

        ll q;
        cin >> q;
        for (ll i = 0; i < q; ++i) {
            ll c, s, e;
            cin >> c >> s >> e;

            vvviii fullGraph(n, vviii(c+1));
            for (ll j = 0; j < n; ++j) {
                for (ll k = 0; k < baseGraph[j].size(); ++k) {
                    ll d = baseGraph[j][k].second;
                    ll v = baseGraph[j][k].first;

                    for (ll l = d; l <= c; ++l) {
                        fullGraph[j][l].push_back(iii(
                    }
                }
            }
        }
    }
    return 0;
}
