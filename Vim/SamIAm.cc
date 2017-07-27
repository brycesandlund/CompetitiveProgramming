#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

bool FindMatch(ll i, vvi &adj_list, vi &mr, vi &mc, vb &seen) {
    for (ll j = 0; j < adj_list[i].size(); ++j) {
        ll item = adj_list[i][j];
        if (!seen[item]) {
            seen[item] = true;
            if (mc[item] < 0 || FindMatch(mc[item], adj_list, mr, mc, seen)) {
                mr[i] = item;
                mc[item] = i;
                return true;
            }
        }
    }
    return false;
}

ll BipartiteMatching(vvi &adj_list, vi &mr, vi &mc) {
    ll ct = 0;
    for (ll i = 0; i < adj_list.size(); ++i) {
        vb seen(mc.size(), false);
        if (FindMatch(i, adj_list, mr, mc, seen)) ct++;
    }
    return ct;
}

void PickRightComponent(vvi &adj_list, vi &mc, ll u, bool left, vi &rp, vb &visited) {
    if (!left) {
        rp.push_back(u);
        PickRightComponent(adj_list, mc, mc[u], !left, rp, visited);
    }
    else {
        visited[u] = true;
        for (ll i = 0; i < adj_list[u].size(); ++i) {
            PickRightComponent(adj_list, mc, adj_list[u][i], !left, rp, visited);
        }
    }
}

int main() {
    ll R, C, N;
    for (ll cs = 1; cin >> R >> C >> N && R; ++cs) {
        vvi adj_list(R);

        for (ll i = 0; i < N; ++i) {
            ll r, c;
            cin >> r >> c;
            --r; --c;
            adj_list[r].push_back(c);
        }

        vi mr(R, -1), mc(C, -1);
        ll matched = BipartiteMatching(adj_list, mr, mc);

        vi lp, rp;
        vb visited(R, false);
        for (ll i = 0; i < R; ++i) {
            if (mr[i] == -1) {
                PickRightComponent(adj_list, mc, i, true, rp, visited);
            }
        }
        for (ll i = 0; i < R; ++i) {
            if (!visited[i])
                lp.push_back(i);
        }
        cout << matched;
        for (ll i = 0; i < rp.size(); ++i)
            cout << " c" << rp[i]+1;
        for (ll i = 0; i < lp.size(); ++i)
            cout << " r" << lp[i]+1;
        cout << endl;
    }
    return 0;
}
