#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll cost(string S) {
    ll strength = 1;
    ll damage = 0;
    for (ll i = 0; i < S.size(); ++i) {
        if (S[i] == 'S')
            damage += strength;
        else
            strength *= 2;
    }
    return damage;
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll D;
        string P;
        cin >> D >> P;

        ll moves = 0;
        while (cost(P) > D) {
            bool shootFound = false;
            ll lastChargeIdx = -1;
            for (ll i = P.size()-1; i >= 0; --i) {
                if (P[i] == 'S') {
                    shootFound = true;
                }
                if (shootFound && P[i] == 'C') {
                    lastChargeIdx = i;
                    break;
                }
            }

            ++moves;
            if (lastChargeIdx != -1)
                swap(P[lastChargeIdx], P[lastChargeIdx+1]);
            else
                break;
        }

        if (cost(P) > D) {
            printf("Case #%lld: IMPOSSIBLE\n", cs);
        }
        else {
            printf("Case #%lld: %lld\n", cs, moves);
        }
    }
}
