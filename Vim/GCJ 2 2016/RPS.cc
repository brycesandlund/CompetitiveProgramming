#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

bool possible(ll R, ll P, ll S) {
    ll total = R + P + S;

    if (total == 2) {
        if (R <= 1 && S <= 1 && P <= 1)
            return true;
        else
            return false;
    }

    ll PS = (total - R*2) / 2;

    if (P >= PS && S >= PS) {
        return possible(S - PS, P - PS, PS);
    }
    else
        return false;
}

int main() {
    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        ll N, R, P, S;
        cin >> N >> R >> P >> S;

        printf("Case #%lld: ", cs);
        if (possible(R, P, S)) {
            ll total = R + P + S;
            ll RS = (total - P*2) / 2;
            ll PR = R - RS;
            ll PS = S - RS;

            ll cur = 0;
            if (RS > PR && PS > PR)
                cur = 1;
            while (RS > 0 || PR > 0 || PS > 0) {
                if (cur == 
            }
            cout << endl;
        }
        else {
            printf("IMPOSSIBLE\n");
        }
    }
}
