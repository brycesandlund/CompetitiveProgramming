#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n, k, p, x, y;
    cin >> n >> k >> p >> x >> y;

    vi marks(n);
    ll over = 0;
    for (ll i = 0; i < k; ++i) {
        cin >> marks[i];
        if (marks[i] >= y) {
            ++over;
        }
    }

    for (ll i = k; i < n; ++i) {
        if (over < (n+1)/2) {
            marks[i] = y;
            ++over;
        }
        else {
            marks[i] = 1;
        }
    }

    ll sum = 0;
    for (ll i = 0; i < n; ++i) {
        sum += marks[i];
    }

    if (y > p || over < (n+1)/2 || sum > x)
        cout << -1 << endl;
    else {
        cout << marks[k];
        for (ll i = k+1; i < n; ++i) {
            cout << " " << marks[i];
        }
        cout << endl;
    }
}
