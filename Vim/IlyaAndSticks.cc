#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 1000040

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n;
    cin >> n;

    vi size(MAXN, 0);
    for (ll i = 0; i < n; ++i) {
        ll cur;
        cin >> cur;
        ++size[cur];
    }

    ll area = 0;
    ll residual = -1;
    for (ll i = MAXN-2; i >= 0; --i) {
        if (size[i+1] % 2 == 1 && size[i] > 0) {
            ++size[i];
        }

        if (residual != -1) {
            if (size[i] >= 2) {
                area += residual * i;
                size[i] -= 2;
                residual = -1;
            }
        }

        ll nSquares = size[i] / 4;
        area += nSquares * i * i;
        size[i] -= nSquares*4;

        if (size[i] >= 2) {
            residual = i;
            size[i] -= 2;
        }
    }

    cout << area << endl;

    return 0;
}
