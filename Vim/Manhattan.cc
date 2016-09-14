#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

struct graph {
    ll N, n_sccs;

    vvi A, B;
    vi scc;

    graph(ll n) : N(n), A(n), B(n), scc(n) {}

    void add_edge(ll s, ll t) {
        A[s].push_back(t);
        B[t].push_back(s);
    }

    bool reachable(ll s, ll t) {
        stack<ll> st;
        st.push(s);
        vb visited(N, false);
        visited[s] = true;

        while (!st.empty()) {
            ll u = st.top(); st.pop();
            if (u == t) return true;
            for (ll i = 0; i < A[u].size(); ++i) {
                if (!visited[A[u][i]]) {
                    st.push(A[u][i]);
                    visited[A[u][i]] = true;
                }
            }
        }
        return false;
    }

    void dfs_order(ll rt, vb &Vis, vi &order) {
        Vis[rt] = true;
        for (ll i = 0; i < A[rt].size(); ++i) {
            ll v = A[rt][i];
            if (Vis[v]) continue;
            dfs_order(v, Vis, order);
        }
        order.push_back(rt);
    }

    void dfs_label(ll rt, vb &Vis, ll lbl, vi &out) {
        Vis[rt] = true;
        out[rt] = lbl;
        for (ll i = 0; i < A[rt].size(); ++i) {
            ll v = A[rt][i];
            if (Vis[v]) continue;
            dfs_label(v, Vis, lbl, out);
        }
    }

    void compute_sccs() {
        vb visited(N, false);
        vi order;
        for (ll v = 0; v < N; ++v) if (!visited[v]) dfs_order(v, visited, order);
        swap(A, B);
        visited = vb(N, false); n_sccs = 0;
        for (ll i = 0; i < N; ++i) {
            ll v = order[N-1-i];
            if (!visited[v]) dfs_label(v, visited, n_sccs++, scc);
        }
        swap(A, B);
    }
};

int main() {
    ll n;
    cin >> n;
    for (ll i = 0; i < n; ++i) {
        ll S, A, m;
        cin >> S >> A >> m;

        graph G((S+A)*2);
        for (ll j = 0; j < m; ++j) {
            ll s1, a1, s2, a2;
            cin >> s1 >> a1 >> s2 >> a2;

            --s1; --a1; --s2; --a2;
            a1 = S*2 + a1*2; a2 = S*2 + a2*2;
            s1 *= 2; s2 *= 2;

       //     cerr << s1 << " " << a1 << " " << s2 << " " << a2 << endl;
            if (s2 < s1) {
                a1 = (a1^1);
                a2 = (a2^1);
            }
            if (a2 < a1) {
                s1 = (s1^1);
                s2 = (s2^1);
            }

        //    cerr << s1 << " " << a1 << " " << s2 << " " << a2 << endl;

            if (s1 == s2 && a1 == a2) {
                // do nothing
            }
            if (s1 == s2) {
                G.add_edge((s1^1), s1);
            }
            else if (a1 == a2) {
                G.add_edge((a1^1), a1);
            }
            else {
                G.add_edge((s1^1), a1);
                G.add_edge((a1^1), s1);
                G.add_edge((a2^1), a1);
                G.add_edge((a1^1), a2);
                G.add_edge((s1^1), s2);
                G.add_edge((s2^1), s1);
                G.add_edge((a2^1), s2);
                G.add_edge((s2^1), a2);
            }
        }

        G.compute_sccs();
        bool success = true;
        for (ll i = 0; i < (S+A)*2; ++i) {
            /*
            if (G.reachable(i, i^1) && G.reachable(i^1, i)) {
                success = false;
                break;
            }
            */
            if (G.scc[i] == G.scc[(i^1)]) {
                success = false;
                break;
            }
        }

        if (success) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    return 0;
}
