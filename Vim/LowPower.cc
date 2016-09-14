#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n, k;
    for (ll cs = 1; cin >> n >> k; ++cs) {
        vi p(2*n*k);
        for (ll i = 0; i < 2*n*k; ++i) {
            cin >> p[i];
        }

        sort(p.begin(), p.end());

        ll lo = -1, hi = 10000000000LL;
        while (lo+1 != hi) {
            ll mid = (lo+hi)/2;
            //cerr << mid << ":" << endl;

            bool success = true;
            ll pairs = 0;
            ll space = 0;
            for (ll i = 1; i < 2*n*k; ++i) {
                if (abs(p[i] - p[i-1]) <= mid) {
                    //cerr << "pair " << p[i] << " with " << p[i-1] << endl;
                    ++pairs;
                    if (pairs == n)
                        break;
                    space += k*2-2;
                    ++i;
                }
                else {
                    if (space == 0) {
                        success = false;
                        break;
                    }
                    --space;
                }
            }

            //cerr << endl;

            if (pairs >= n) {
                hi = mid;
            }
            else {
                lo = mid;
            }
        }
        cout << hi << endl;
    }
}
