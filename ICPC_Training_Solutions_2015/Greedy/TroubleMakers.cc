#include <iostream>
#include <vector>
#include <set>
#include <cstdio>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

int main() {
    ll N;
    cin >> N;
    for (ll cs = 1; cs <= N; ++cs) {
        ll n, m;
        cin >> n >> m;
        vvi adj_list(n);

        for (ll i = 0; i < m; ++i) {
            ll u, v;
            cin >> u >> v;
            --u;
            --v;
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }

        vb move(n, false);
        ll n_moved = 0;

        bool change = true;
        while(change) {
            change = false;
            for (ll i = 0; i < n; ++i) {
                ll same = 0;
                for (ll j = 0; j < adj_list[i].size(); ++j) {
                    if (move[adj_list[i][j]] == move[i])
                        ++same;
                }

                if (same > adj_list[i].size()/2) {
                    if (move[i]) {
                        --n_moved;
                        move[i] = false;
                    }
                    else {
                        ++n_moved;
                        move[i] = true;
                    }
                    change = true;
                }
            }
        }

        printf("Case #%lld: %lld\n", cs, n_moved);
        bool first = true;
        for (ll i = 0; i < n; ++i) {
            if (move[i]) {
                if (first) {
                    cout << i+1;
                    first = false;
                }
                else
                    cout << " " << i+1;
            }
        }
        cout << endl;
    }
    return 0;
}
