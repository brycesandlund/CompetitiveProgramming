#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF 10000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<string> vs;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef vector<iii> viii;
typedef vector<viii> vviii;
typedef vector<vviii> vvviii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<vvii> vvvii;


int main() {
    ll n, m, f, s, t;
    cin >> n >> m >> f >> s >> t;

    // adj_list[start city][flight][vertex i] = iii(new_flight, ii(end city, cost))
    vvviii adj_list(n, vviii(2));
    
    for (ll i = 0; i < m; ++i) {
        ll u, v, c;
        cin >> u >> v >> c;
        adj_list[u][0].push_back(iii(0, ii(v, c)));
        adj_list[u][1].push_back(iii(1, ii(v, c)));
        adj_list[v][0].push_back(iii(0, ii(u, c)));
        adj_list[v][1].push_back(iii(1, ii(u, c)));
    }

    for (ll i = 0; i < f; ++i) {
        ll u, v;
        cin >> u >> v;
        adj_list[u][0].push_back(iii(1, ii(v, 0)));
    }

    vvi dist(n, vi(2, INF));

    // iii(cost, ii(city, flight))
    priority_queue<iii, viii, std::greater<iii> > q;
    q.push(iii(0, ii(s, 0)));
    while (!q.empty()) {
        ll u = q.top().second.first;
        ll flight = q.top().second.second;
        ll cost = q.top().first;
        q.pop();

        if (dist[u][flight] == INF) {
            dist[u][flight] = cost;

            for (ll i = 0; i < adj_list[u][flight].size(); ++i) {
                ll v = adj_list[u][flight][i].second.first;
                ll c = adj_list[u][flight][i].second.second;
                ll f = adj_list[u][flight][i].first;

                q.push(iii(c + cost, ii(v, f)));
            }
        }
    }


    cout << min(dist[t][1], dist[t][0]) << endl;
}
