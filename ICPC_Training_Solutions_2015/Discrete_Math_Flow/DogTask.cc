#include <iostream>
#include <vector>
#include <cmath>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
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

double d(ii one, ii two) {
    ll dx = one.first - two.first;
    ll dy = one.second - two.second;

    return sqrt(dx*dx + dy*dy);
}

int main() {
    ll L;
    cin >> L;
    for (ll cs = 1; cs <= L; ++cs) {
        ll N, M;
        cin >> N >> M;

        vii bob(N);
        for (ll i = 0; i < N; ++i) {
            cin >> bob[i].first >> bob[i].second;
        }

        vii interesting(M);
        for (ll i = 0; i < M; ++i) {
            cin >> interesting[i].first >> interesting[i].second;
        }

        vvi adj_list(N-1);
        for (ll i = 0; i < N-1; ++i) {
            for (ll j = 0; j < M; ++j) {
                double master = d(bob[i], bob[i+1]);
                double dog = d(bob[i], interesting[j]) + d(interesting[j], bob[i+1]);
                if (dog <= master*2 + EP) {
                    adj_list[i].push_back(j);
                }
            }
        }
        
        vi mr(N-1, -1), mc(M, -1);
        ll matched = BipartiteMatching(adj_list, mr, mc);

        if (cs != 1) {
            cout << endl;
        }

        cout << matched + N << endl;
        for (ll i = 0; i < N-1; ++i) {
            cout << bob[i].first << " " << bob[i].second << " ";
            if (mr[i] != -1) {
                cout << interesting[mr[i]].first << " " << interesting[mr[i]].second << " ";
            }
        }
        cout << bob[N-1].first << " " << bob[N-1].second << endl;
    }
    return 0;
}
