#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

int main() {
    ll n;
    for (ll cs = 1; cin >> n && n != -1; ++cs) {
        vvi adj_matrix(n, vi(n));
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < n; ++j) {
                cin >> adj_matrix[i][j];
            }
        }

        vb weak(n, true);
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < n; ++j) {
                if (j == i) continue;
                if (adj_matrix[i][j] == 0) continue;

                for (ll k = 0; k < n; ++k) {
                    if (adj_matrix[j][k] == 0) continue;

                    if (adj_matrix[i][k] == 1) {
                        weak[i] = false;
                    }
                }
            }
        }

        bool has_printed = false;
        for (ll i = 0; i < n; ++i) {
            if (weak[i]) {
                if (has_printed)
                    cout << " ";

                cout << i;
                has_printed = true;
            }
        }

        cout << endl;
    }
}
