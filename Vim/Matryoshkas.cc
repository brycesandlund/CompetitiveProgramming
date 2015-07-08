#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll n, k;
    cin >> n >> k;

    vvi dolls(k);

    for (ll i = 0; i < k; ++i) {
        ll m;
        cin >> m;
        dolls[i] = vi(m);
        for (ll j = 0; j < m; ++j) {
            cin >> dolls[i][j];
        }
    }
    
    ll pieces = k;
    ll moves = 0;

    for (ll i = 0; i < k; ++i) {
        bool keep = false;
        if (dolls[i][0] == 1) {
            keep = true;
        }
        for (ll j = 1; j < dolls[i].size(); ++j) {
            if (dolls[i][j] - dolls[i][j-1] > 1 || !keep) {
                ++moves;
                ++pieces;
                keep = false;
            }
        }
    }

    moves += pieces-1;

    cout << moves << endl;

    return 0;
}
