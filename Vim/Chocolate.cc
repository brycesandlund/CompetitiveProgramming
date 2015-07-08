#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll get_height(ll x, vii &heights) {
    vii::iterator it = heights.lower_bound(ii(x, -1));
    return it->second;
}

void insert_height(ll x, vii &heights) {
    vii::iterator it = heights.lower_bound(ii(x, -1));

}

int main() {
    ll n, q;
    cin >> n >> q;
    vii horz;
    vii vert;

    horz.push_back(n, 0);
    vert.push_back(n, 0);

    for (ll i = 0; i < q; ++i) {
        ll x, y;
        cin >> x >> y;
        char c;
        cin >> ws >> c;
        if (c == 'U') {
            ll stoppt = get_height(x, horz);
            cout << y - stoppt << endl;

        }
    }
}
