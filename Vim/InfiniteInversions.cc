#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int main() {
    ll n;
    cin >> n;
    
    vii swaps(n);
    for (ll i = 0; i < n; ++i) {
        ll a_i, b_i;
        cin >> a_i >> b_i;
        swaps[i] = ii(max(a_i, b_i), min(a_i, b_i));
    }

    sort(swaps.begin(), swaps.end());
    set<ll> 

    return 0;
}
