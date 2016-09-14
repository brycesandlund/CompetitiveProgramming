#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; ++i) {
        ll c, d;
        cin >> d >> c;

        if (c == 1 && d == 1) {
            cout << "AMBIGUOUS" << endl;
        }
        else if ((d == 1 && c != 1) || (d == 0 && c != 0)) {
            cout << "IMPOSSIBLE" << endl;
        }
        else if (c == 0 && d == 0) {
            cout << 0 << endl;
        }
        else if (c <= 0 || d <= 0) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            vi base_d;
            ll sum = 0;
            while (c > 0) {
                base_d.push_back(c % d);
                c /= d;
                sum += base_d.back();
            }

            if (sum == d) {
                for (ll j = base_d.size()-1; j >= 1; --j) {
                    cout << base_d[j] << " ";
                }
                cout << base_d[0] << endl;
            }
            else {
                cout << "IMPOSSIBLE" << endl;
            }
        }
    }
    return 0;
}
