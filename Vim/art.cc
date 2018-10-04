#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    vi l(5);
    for (ll i = 0; i < 5; ++i) {
        cin >> l[i];
    }

    sort(l.rbegin(), l.rend());

    ll triangles = 0;
    for (ll i = 0; i < 5; ++i)
        for (ll j = i+1; j < 5; ++j)
            for (ll k = j+1; k < 5; ++k) {
                if (l[j] + l[k] > l[i]) ++triangles;
            }

    cout << triangles << endl;
}
