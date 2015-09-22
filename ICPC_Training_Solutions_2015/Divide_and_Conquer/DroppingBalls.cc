#include <iostream>

using namespace std;

typedef long long ll;

ll solve(ll D, ll I) {
    if (D == 1)
        return 1;

    if (I % 2 == 0) {
        return solve(D-1, (I+1)/2) + (1 << (D-2));  // 2^(D-2)
    }
    else {
        return solve(D-1, (I+1)/2);
    }
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll D, I;
        cin >> D >> I;

        cout << solve(D, I) + (1 << (D-1)) - 1 << endl;
    }
    return 0;
}
