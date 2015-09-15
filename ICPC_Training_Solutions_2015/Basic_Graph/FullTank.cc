#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <functional>

#define INF 1000000000000000000LL

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

            priority_queue<iii, viii, greater<iii> > pq;
            vvi best(n, vi(c+1, INF));
            pq.push(iii(0, ii(s, 0)));

            ll ans = -1;
            while (!pq.empty()) {
                ll city = pq.top().second.first;
                ll tank = pq.top().second.second;
                ll cost = pq.top().first;

                pq.pop();

                if (cost > best[city][tank])
                    continue;

                if (city == e) {
                    ans = cost;
                    break;
                }

                for (ll i = 0; i < baseGraph[city].size(); ++i) {
                    ll v = baseGraph[city][i].first;
                    ll d = baseGraph[city][i].second;

                    if (d > tank)
                        continue;

                    if (cost < best[v][tank-d]) {
                        best[v][tank-d] = cost;
                        pq.push(iii(cost, ii(v, tank-d)));
                    }
                }

                ll cost_buy = cost + p[city];
                if (tank < c && cost_buy < best[city][tank+1]) {
                    best[city][tank+1] = cost_buy;
                    pq.push(iii(cost_buy, ii(city, tank+1)));
                }
            }

            if (ans == -1)
                cout << "impossible" << endl;
            else
                cout << ans << endl;
        }
    }
    return 0;
}
