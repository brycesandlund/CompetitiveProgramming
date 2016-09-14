#include <iostream>
#include <vector>
#include <unordered_map>

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

ll get_row(double slope, unordered_map<double, ll> &slope_to_row) {
    if (!slope_to_row.count(slope)) {
        ll size = slope_to_row.size();
        slope_to_row[slope] = size;
    }

    return slope_to_row[slope];
}

ll get_col(ll radius, unordered_map<ll, ll> &radius_to_col) {
    if (!radius_to_col.count(radius)) {
        ll size = radius_to_col.size();
        radius_to_col[radius] = size;
    }

    return radius_to_col[radius];
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll n;
        cin >> n;

        unordered_map<double, ll> slope_to_row;
        unordered_map<ll, ll> radius_to_col;

        vvi adj_list;

        for (ll i = 0; i < n; ++i) {
            ll ri, si, ti;
            cin >> ri >> si >> ti;
            
            ll u = get_row((double)ti / si, slope_to_row);
            ll v = get_col(ri, radius_to_col);

            if (adj_list.size() == u) {
                adj_list.push_back(vi());
            }

            adj_list[u].push_back(v);
        }

        vi mr(slope_to_row.size(), -1);
        vi mc(radius_to_col.size(), -1);

        cout << BipartiteMatching(adj_list, mr, mc) << endl;
    }
    return 0;
}
