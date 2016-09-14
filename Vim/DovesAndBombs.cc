#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

bool myfunction(ii left, ii right) {
    if (left.second == right.second)
        return left.first < right.first;
    else
        return left.second >= right.second;
}

struct artbridge_graph {
    ll N; vvi adj;
    vi parent, n_children, rank;
    vi is_art; vi reach;
    vb visited; ll R;

    artbridge_graph(ll N) : N(N), adj(N), is_art(N) {}
    void add_edge(ll s, ll t) {
        adj[s].push_back(t);
        adj[t].push_back(s);
    }
    void dfs_artpts(ll rt) {
        visited[rt] = true;
        rank[rt] = R++;
        reach[rt] = rank[rt];
        for (ll i = 0; i < adj[rt].size(); ++i) {
            ll v = adj[rt][i];
            if (v == parent[rt]) continue;
            if (visited[v])
                reach[rt] = min(reach[rt], rank[v]);
            else {
                ++n_children[rt];
                parent[v] = rt;
                dfs_artpts(v);
                reach[rt] = min(reach[rt], reach[v]);
                if (reach[v] >= rank[rt]) {
                    ++is_art[rt];
                }
            }
        }
    }
    void comp_artbridge() {
        is_art = vi(N, 0); reach = vi(N);
        parent = vi(N,N); rank = vi(N); n_children = vi(N,0);
        visited = vb(N,false); R = 0;
        for (ll i = 0; i < N; ++i) {
            if (visited[i]) continue;
            dfs_artpts(i);
            is_art[i] = n_children[i]-1;
        }
    }
};

int main() {
    ll n, m;
    while (cin >> n >> m && !(n == 0 && m == 0)) {
        artbridge_graph G(n);
        ll x, y;
        while (cin >> x >> y && !(x == -1 && y == -1)) {
            G.add_edge(x, y);
        }
        G.comp_artbridge();

        vii results(n);
        for (ll i = 0; i < n; ++i) {
            results[i] = ii(i, G.is_art[i]+1);
        }
        sort(results.begin(), results.end(), myfunction);

        for (ll i = 0; i < m; ++i) {
            cout << results[i].first << " " << results[i].second << endl;
        }
        cout << endl;
    }
    return 0;
}
