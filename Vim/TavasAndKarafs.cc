#include <iostream>

#define INF 100000000000LL;

using namespace std;

typedef long long ll;

int main() {
    ll A, B, n;
    cin >> A >> B >> n;

    for (ll i = 0; i < n; ++i) {
        ll l, t, m;
        cin >> l >> t >> m;

        ll lo = l-1;
        ll hi = INF;

        while (lo != hi-1) {
            ll r = (lo+hi)/2;

            //cerr << r << endl;
            ll hr = A + (r-1)*B;

            bool success = t >= hr;
            
            if (success) {
                ll hl = A + (l-1)*B;

                ll volume = (hr+hl) * (r-l+1) / 2;
                
                if (t*m < volume) {
                    success = false;
                }
            }

            if (success)
                lo = r;
            else
                hi = r;
        }

        if (lo >= l)
            cout << lo << endl;
        else
            cout << -1 << endl;
    }

    return 0;
}
