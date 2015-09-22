#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll N;
    cin >> N;
    vi ladies(N);
    for (ll i = 0; i < N; ++i) {
        cin >> ladies[i];
    }

    ll Q;
    cin >> Q;
    for (ll i = 0; i < Q; ++i) {
        ll height;
        cin >> height;
        vi::iterator lower = lower_bound(ladies.begin(), ladies.end(), height);
        if (lower == ladies.begin()) {
            cout << "X";
        }
        else {
            --lower;
            cout << *lower;
        }

        cout << " ";
        vi::iterator upper = upper_bound(ladies.begin(), ladies.end(), height);
        if (upper == ladies.end()) {
            cout << "X";
        }
        else {
            cout << *upper;
        }

        cout << endl;
    }
    return 0;
}
