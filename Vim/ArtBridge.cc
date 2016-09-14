#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

struct graph {
    ll N;
    vvi adj;
    vi parent, n_children, rank;
    vb is_art; vi reach;

    graph(ll N) : N(N), adj(N), is_art(N) {}
    void add_edge(ll s, ll t) {
        adj[s].push_back(t);
        adj[t].push_back(s);
    }

    ll dfs_artpts(ll rt, vb &visited, ll R) {
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
                R = dfs_artpts(v, visited, R);
                reach[rt] = min(reach[rt], reach[v]);
            }
            if (reach[v] >= rank[rt])
                is_art[rt] = true;
        }
        return R;
    }

    void comp_art_pts() {
        is_art = vb(N, false); reach = vi(N);
        parent = vi(N, N); rank = vi(N); n_children = vi(N,0);
        vb visited(N, false); ll R = 0;
        for (ll i = 0; i < N; ++i) {
            if (visited[i]) continue;
            R = dfs_artpts(i, visited, R);
            is_art[i] = (n_children[i] >= 2);
        }
    }
};

int main() {
    graph g(6);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 0);
    g.add_edge(1, 4);
    g.add_edge(4, 5);
    g.comp_art_pts();
    cerr << g.is_art[4] << endl;
    return 0;
}
