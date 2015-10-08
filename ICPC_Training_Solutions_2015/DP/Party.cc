#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;


ll get(string s, unordered_map<string, ll> &mp, vvi &children) {
    if (!mp.count(s)) {
        ll size = mp.size();
        mp[s] = size;
        children.push_back(vi());
    }

    return mp[s];
}

void solve(ll idx, vvi &children, vb &in_unique, vb &out_unique, vi &in_best, vi &out_best) {
    for (ll i = 0; i < children[idx].size(); ++i) {
        solve(children[idx][i], children, in_unique, out_unique, in_best, out_best);
    }

    for (ll i = 0; i < children[idx].size(); ++i) {
        in_unique[idx] = in_unique[idx] && out_unique[children[idx][i]];
        in_best[idx] += out_best[children[idx][i]];
    }
    ++in_best[idx];

    for (ll i = 0; i < children[idx].size(); ++i) {
        ll out_child = out_best[children[idx][i]];
        ll in_child = in_best[children[idx][i]];
        
        if (in_child > out_child) {
            out_best[idx] += in_child;
            out_unique[idx] = out_unique[idx] && in_unique[children[idx][i]];
        }
        else if (in_child < out_child) {
            out_best[idx] += out_child;
            out_unique[idx] = out_unique[idx] && out_unique[children[idx][i]];
        }
        else {
            out_best[idx] += in_child;
            out_unique[idx] = false;
        }
    }
}

int main() {
    ll n;
    for (ll cs = 1; cin >> n && n; ++cs) {

        unordered_map<string, ll> mp;

        vvi children;

        string bb;
        cin >> bb;

        ll root = get(bb, mp, children);

        for (ll i = 0; i < n-1; ++i) {
            string emp, boss;
            cin >> emp >> boss;

            ll boss_idx = get(boss, mp, children);
            ll emp_idx = get(emp, mp, children);
            children[boss_idx].push_back(emp_idx);
        }

        vb in_unique(mp.size(), true), out_unique(mp.size(), true);
        vi in_best(mp.size(), 0), out_best(mp.size(), 0);

        solve(root, children, in_unique, out_unique, in_best, out_best);
        
        if (in_best[root] > out_best[root]) {
            cout << in_best[root] << " " << (in_unique[root] ? "Yes" : "No") << endl;
        }
        else if (in_best[root] < out_best[root]) {
            cout << out_best[root] << " " << (out_unique[root] ? "Yes" : "No") << endl;
        }
        else {
            cout << in_best[root] << " No" << endl;
        }
    }
    return 0;
}
