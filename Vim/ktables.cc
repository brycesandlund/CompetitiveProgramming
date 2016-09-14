#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll n, k;
    cin >> n >> k;

    --k;
    vvi table(n, vi(n));

    ll counter = n*n;
    for (ll i = 0; i < n; ++i) {
        for (ll j = n-1; j >= k; --j) {
            table[i][j] = counter--;
        }
    }

    ll sum = 0;
    for (ll i = 0; i < n; ++i) {
        sum += table[i][k];
    }

    cout << sum << endl;

    for (ll i = 0; i < n; ++i) {
        for (ll j = k-1; j >= 0; --j) {
            table[i][j] = counter--;
        }
    }

    for (ll i = 0; i < n; ++i) {
        cout << table[i][0];
        for (ll j = 1; j < n; ++j) {
            cout << " " << table[i][j];
        }
        cout << endl;
    }
    return 0;
}
