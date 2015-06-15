#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;

int main() {
    ll n, m;
    cin >> n >> m;

    vvb apartment(n, vb(m));

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            char c;
            cin >> ws >> c;
            if (c == '.')
                apartment[i][j] = true;
            else
                apartment[i][j] = false;
        }
    }

    vvb visited(n, vb(m, false));

    return 0;
}
