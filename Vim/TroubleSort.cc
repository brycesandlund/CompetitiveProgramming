#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll N;
        cin >> N;
        vi V(N);
        vi V_even;
        vi V_odd;
        for (ll i = 0; i < N; ++i) {
            cin >> V[i];
            if (i % 2 == 0)
                V_even.push_back(V[i]);
            else
                V_odd.push_back(V[i]);
        }
        sort(V.begin(), V.end());
        sort(V_even.begin(), V_even.end());
        sort(V_odd.begin(), V_odd.end());
        
        vi V_new(N);
        for (ll i = 0; i < N; ++i) {
            if (i % 2 == 0)
                V_new[i] = V_even[i/2];
            else
                V_new[i] = V_odd[i/2];
        }

        ll first_wrong = -1;
        for (ll i = 0; i < N; ++i) {
            if (V[i] != V_new[i]) {
                first_wrong = i;
                break;
            }
        }

        cout << "Case #" << cs << ": ";
        if (first_wrong == -1)
            cout << "OK" << endl;
        else
            cout << first_wrong << endl;
    }
}
