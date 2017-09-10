#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

int main() {
    ll n, m;
    for (ll cs = 1; cin >> n >> m && n != 0; ++cs) {
        vi head(n);
        multiset<ll> knight;
        for (ll i = 0; i < n; ++i)
            cin >> head[i];
        for (ll i = 0; i < m; ++i) {
            ll knight_i;
            cin >> knight_i;
            knight.insert(knight_i);
        }

        ll gold = 0;
        bool success = true;
        for (ll i = 0; i < n; ++i) {
            auto it = knight.lower_bound(head[i]);
            if (it == knight.end()) {
                success = false;
                break;
            }
            gold += *it;
            knight.erase(it);
        }

        if (success) {
            cout << gold << endl;
        }
        else
            cout << "Loowater is doomed!" << endl;
    }
}
