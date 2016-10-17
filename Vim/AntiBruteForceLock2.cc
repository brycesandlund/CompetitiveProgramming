#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef vector<iii> viii;

ll find(vi &C, ll x) { return (C[x] == x) ? x : C[x] = find(C, C[x]); }
void merge(vi &C, ll x, ll y) { C[find(C, x)] = find(C, y); }

ll kruskal(viii &edges, ll n) {
    sort(edges.begin(), edges.end());

    vi uf(n);
    for (ll i = 0; i < n; ++i)
        uf[i] = i;

    ll cost = 0;
    for (ll i = 0; i < edges.size(); ++i) {
        ll u = edges[i].second.first;
        ll v = edges[i].second.second;

        if (find(uf, u) != find(uf, v)) {
            merge(uf, u, v);
            cost += edges[i].first;
        }
    }
    return cost;
}

ll roll_cost(string s, string t) {
    ll cost = 0;
    for (ll k = 0; k < 4; ++k) {
        cost += min(abs(s[k]-t[k]), min(10-s[k]+t[k], s[k]+10-t[k]));
    }
    return cost;
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll N;
        cin >> N;
        vs keys(N);
        for (ll i = 0; i < N; ++i) {
            cin >> keys[i];
        }

        viii edges;
        for (ll i = 0; i < N; ++i) {
            for (ll j = 0; j < N; ++j) {
                edges.push_back(iii(roll_cost(keys[i], keys[j]), ii(i, j)));
            }
        }

        ll cost = kruskal(edges, N);
        
        string start_str = "0000";
        ll minStart = roll_cost(start_str, keys[0]);
        for (ll i = 1; i < N; ++i) {
            minStart = min(minStart, roll_cost(start_str, keys[i]));
        }
        cost += minStart;

        cout << cost << endl;
    }
    return 0;
}
