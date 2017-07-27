#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll n;
    cin >> n;

    vi a(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    vi best(n+3, INF);
    best[n] = 0;
    best[n+1] = 0;
    best[n+2] = 0;
    best[n-1] = a[n-1] - a[n-2];
    best[n-2] = a[n-1] - a[n-2];

    for (ll i = n-3; i >= 2; --i) {
        best[i] = a[i] - a[i-1] + a[i+2] - a[i+1] + best[i+3];
        best[i] = min(best[i], a[i+1] - a[i] + best[i+2]);
    }

    best[0] = a[1] - a[0] + best[2];

    cout << best[0] << endl;
}
