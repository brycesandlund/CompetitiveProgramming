#include <iostream>
#include <vector>

#define INF 1000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll l1, l2;
    string x, y;
    for (ll cs = 1; cin >> l1 >> x >> l2 >> y; ++cs) {
        vvi best(l1+1, vi(l2+1, INF));
        for (ll i = 0; i < l1+1; ++i) {
            best[i][0] = i;
        }
        for (ll j = 0; j < l2+1; ++j) {
            best[0][j] = j;
        }

        for (ll i = 1; i < l1+1; ++i) {
            for (ll j = 1; j < l2+1; ++j) {
                if (x[i-1] == y[j-1]) {
                    best[i][j] = best[i-1][j-1];
                }

                best[i][j] = min(best[i][j], best[i-1][j-1]+1);
                best[i][j] = min(best[i][j], best[i-1][j]+1);
                best[i][j] = min(best[i][j], best[i][j-1]+1);
            }
        }

        cout << best[l1][l2] << endl;
    }
    return 0;
}
