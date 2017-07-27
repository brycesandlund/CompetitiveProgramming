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
            ll RS = (R+P+S - P*2) / 2;
            R -= RS;
            
            for (ll i = 0; i < P; ++i) {
                cout << "P";

                if (R > 0) {
                    cout << "R";
                    --R;
                }
                else {
                    cout << "S";
                }
            }

            for (ll i = 0; i < RS; ++i) {
                cout << "RS";
            }
            cout << endl;
        }
        else {
            printf("IMPOSSIBLE\n");
        }
    }
}
