#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n, w;
    cin >> n >> w;

    vi a(2*n);
    for (ll i = 0; i < a.size(); ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    ll girl_min = a[0];
    ll boy_min = a[n];

    ll amountGirl = min(girl_min*2, boy_min);
    ll amountTotal = amountGirl*n + amountGirl*n*2;
    ll ans = min(w*2, amountTotal);

    if (ans % 2 == 0) {
        cout << ans/2 << endl;
    }
    else {
        cout << ans/2 << ".5" << endl;
    }
    return 0;
}
