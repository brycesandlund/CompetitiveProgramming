#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n, k;
    cin >> n >> k;
    vi a(k);
    for (ll i = 0; i < k; ++i) {
        cin >> a[i];
    }

    sort(a.rbegin(), a.rend());
    ll smallsum = 0;
    for (ll i = 1; i < k; ++i) {
        smallsum += a[i];
    }
    ll total = smallsum + a[0];
    ll unmatched = max(a[0] - smallsum, 0LL);
    
    if (unmatched == 0 && total % 2 == 1)
        unmatched = 1;

    ll needed_pairs = (total - unmatched) / 2 + unmatched;

    if (needed_pairs <= n*4)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
