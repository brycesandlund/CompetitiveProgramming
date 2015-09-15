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

struct union_find {
    vi parent;
    vi size;

    union_find(ll n) {
        parent.resize(n);
        size.resize(n, 1);
        for (ll i = 0; i < n; ++i)
            parent[i] = i;
    }

    ll find(ll i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    void merge(ll i, ll j) {
        if (size[find(i)] < size[find(j)])
            merge(j, i);
        parent[find(j)] = parent[find(i)];
        size[find(i)] += size[find(j)];
    }
};

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

        sort(edges.begin(), edges.end());
        union_find uf(N+1);
        ll cost = 0;
        for (ll i = 0; i < edges.size(); ++i) {
            ll u = edges[i].second.first;
            ll v = edges[i].second.second;
            if (uf.find(u) != uf.find(v)) {
                uf.merge(u, v);
                cost += edges[i].first;
            }
        }
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
