#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;


int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll n;
        cin >> n;

        vi books(n);
        for (ll i = 0; i < n; ++i) {
            cin >> books[i];
        }

        ll total_cost = 0;
        for (ll i = 1; i < n; ++i) {
            if (books[i] >= books[i-1])
                continue;

            ll spot = lower_bound(books.begin(), books.begin()+i+1, books[i]) - books.begin();

            ll num = spot == 0 ? 1 : 2;
            ll cost = 1;
            for (ll j = 1; j < spot; ++j) {
                if (books[j] == books[j-1]) {
                    ++num;
                }
                else {
                    cost *= num;
                    num = 2;
                }
            }
            cost *= num;
            total_cost += cost;

            sort(books.begin(), books.begin()+i+1);
        }

        cout << total_cost << endl;
    }
    return 0;
}
