#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

int main() {
    ll n;
    cin >> n;

    string original;
    cin >> original;

    string combo;
    cin >> combo;

    ll minMoves = 0;
    for (ll i = 0; i < n; ++i) {
        ll curMove = abs(combo[i] - original[i]);
        curMove = min(curMove, (ll)(original[i] - '0' + '9' - combo[i] + 1));
        curMove = min(curMove, (ll)('9' - original[i] + combo[i] - '0' + 1));
        minMoves += curMove;
    }

    cout << minMoves << endl;

    return 0;
}
