#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef vector<double> vi;
typedef vector<vi> vvi;
typedef pair<double, ll> ii;
typedef vector<ii> vii;

int main() {
    ll n;
    cin >> n;

    vvi matrix(n, vi(n));
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    vii order(n);
    for (ll i = 0; i < n; ++i) {
        order[i] = ii(matrix[0][i], i);
    }
    order[0] = ii(1, 0);

    sort(order.begin(), order.end());
    vi prob(n, 0);
    prob[order[0].second] = 1;

    for (ll i = 1; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            prob[order[i].second] += matrix[order[i].second][j] * prob[j]; 
        }
        
        for (ll j = 0; j < n; ++j) {
            if (j == order[i].second)
                continue;
            prob[j] = prob[j] * matrix[j][order[i].second];
        }

    }

    cout << setprecision(10);
    cout << fixed;
    cout << prob[0] << endl;

    return 0;
}
