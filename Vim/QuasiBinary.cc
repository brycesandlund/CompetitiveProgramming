#include <iostream>
#include <vector>
#include <cstdlib>

#define INF 1000000000
#define MAXN 1000040
//#define MAXN 100

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    string n;
    cin >> n;

    vector<string> parts(9, string(n.size(), '0'));
    ll maxPart = 0;
    for (ll i = 0; i < n.size(); ++i) {
        for (ll j = 0; j < n[i] - '0'; ++j) {
            parts[j][i] = '1';
            maxPart = max(maxPart, j);
        }
    }

    cout << maxPart+1 << endl;
    cout << atoi(parts[0].c_str());
    for (ll i = 1; i <= maxPart; ++i) {
        cout << " " << atoi(parts[i].c_str());
    }
    cout << endl;

    return 0;
}
