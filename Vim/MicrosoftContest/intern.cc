#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll n;
    cin >> n;
    vvi nums(n, vi(n));
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j <= i; ++j) {
            cin >> nums[i][j];
        }
    }

    vvi best(n, vi(n));
    best[n-1] = nums[n-1];

    for (ll i = n-2; i >= 0; --i) {
        for (ll j = 0; j <= i; ++j) {
            best[i][j] = nums[i][j] + max(best[i+1][j], best[i+1][j+1]);
        }
    }

    cout << best[0][0] << endl;
    return 0;
}
