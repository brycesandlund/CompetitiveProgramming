#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef unordered_map<ll, ll> mii;

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

void PickRightComponent(vvi &adj_list, vi &mc, ll u, bool left, vi &rp, vb &visited_l, vb &visited_r) {
    if (!left) {
        if (!visited_r[u]) {
            visited_r[u] = true;
            rp.push_back(u);
            PickRightComponent(adj_list, mc, mc[u], !left, rp, visited_l, visited_r);
        }
    }
    else {
        visited_l[u] = true;
        for (ll i = 0; i < adj_list[u].size(); ++i) {
            PickRightComponent(adj_list, mc, adj_list[u][i], !left, rp, visited_l, visited_r);
        }
    }
}

ll gridToIdx(mii &mp, ll spot, vi &idxToGrid) {
    if (mp.count(spot)) {
        return mp[spot];
    }
    else {
        ll size = mp.size();
        idxToGrid.push_back(spot);
        return mp[spot] = size;
    }
}

int main() {
    ll R, C, N;
    for (ll cs = 1; cin >> R >> C >> N && R; ++cs) {
        mii rowToIdx, colToIdx;
        vi idxToRow, idxToCol;
        
        vvi adj_list;

        for (ll i = 0; i < N; ++i) {
            ll r, c;
            cin >> r >> c;

            ll r_idx = gridToIdx(rowToIdx, r, idxToRow);
            ll c_idx = gridToIdx(colToIdx, c, idxToCol);
            
            if (r_idx == adj_list.size()) {
                adj_list.push_back(vi(0));
            }
            adj_list[r_idx].push_back(c_idx);
        }

        vi mr(rowToIdx.size(), -1), mc(colToIdx.size(), -1);
        ll matched = BipartiteMatching(adj_list, mr, mc);

        vi lp, rp;
        vb visited_l(rowToIdx.size(), false);
        vb visited_r(colToIdx.size(), false);
        for (ll i = 0; i < rowToIdx.size(); ++i) {
            if (mr[i] == -1) {
                PickRightComponent(adj_list, mc, i, true, rp, visited_l, visited_r);
            }
        }
        for (ll i = 0; i < rowToIdx.size(); ++i) {
            if (!visited_l[i])
                lp.push_back(i);
        }
        cout << matched;
        for (ll i = 0; i < rp.size(); ++i)
            cout << " c" << idxToCol[rp[i]];
        for (ll i = 0; i < lp.size(); ++i)
            cout << " r" << idxToRow[lp[i]];
        cout << endl;
    }
    return 0;
}
