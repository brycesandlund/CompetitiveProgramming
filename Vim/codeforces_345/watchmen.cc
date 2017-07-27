#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

int main() {
    ll n;
    cin >> n;

    map<ll, ll> row_count, col_count;
    map<ii, ll> coord_count;

    ll total = 0;
    for (ll i = 0; i < n; ++i) {
        ll x, y;
        cin >> x >> y;

        if (row_count.count(x) == 0)
            row_count[x] = 0;
        if (col_count.count(y) == 0)
            col_count[y] = 0;
        if (coord_count.count(ii(x, y)) == 0)
            coord_count[ii(x, y)] = 0;

        total += row_count[x] + col_count[y] - coord_count[ii(x, y)];
        ++row_count[x];
        ++col_count[y];
        ++coord_count[ii(x, y)];
    }

    cout << total << endl;
}
