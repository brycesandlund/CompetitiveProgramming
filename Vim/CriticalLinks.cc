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

struct artbridge_graph {
    ll N; vvi adj;
    vi parent, n_children, rank;
    vi reach;
    vb visited; ll R;
    vii bridges;

    artbridge_graph(ll N) : N(N), adj(N) {}
    void add_edge(ll s, ll t) {
        adj[s].push_back(t);
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
                if (reach[v] > rank[rt]) {
                    bridges.push_back(ii(min(v, rt), max(v, rt)));
                }
            }
        }
    }
    void comp_artbridge() {
        reach = vi(N);
        parent = vi(N,N); rank = vi(N); n_children = vi(N,0);
        visited = vb(N,false); R = 0;
        for (ll i = 0; i < N; ++i) {
            if (visited[i]) continue;
            dfs_artpts(i);
        }
    }
};

int main() {
    ll n;
    for (ll cs = 1; cin >> n; ++cs) {
        artbridge_graph G(n);
        
        for (ll i = 0; i < n; ++i) {
            ll u, size;
            scanf("%llu (%llu)", &u, &size);
            for (ll j = 0; j < size; ++j) {
                ll v;
                cin >> v;
                G.add_edge(u, v);
            }
        }

        G.comp_artbridge();
        cout << G.bridges.size() << " critical links" << endl;
        sort(G.bridges.begin(), G.bridges.end());

        for (ll i = 0; i < G.bridges.size(); ++i) {
            cout << G.bridges[i].first << " - " << G.bridges[i].second << endl;
        }
        cout << endl;
    }
}
