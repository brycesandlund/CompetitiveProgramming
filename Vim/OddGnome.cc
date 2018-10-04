#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n;
    cin >> n;
    for (ll i = 0; i < n; ++i) {
        ll g;
        cin >> g;

        vi gnome(g);
        for (ll j = 0; j < g; ++j) {
            cin >> gnome[j];
        }
        for (ll j = 1; j < g; ++j) {
            if (gnome[j] != gnome[j-1]+1) {
                cout << j+1 << endl;
                break;
            }
        }
    }
}
