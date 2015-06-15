#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<string> vs;

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        string s;
        cin >> s;
        ll n = s.size();
        s = s + s;

        vs linear;
        for (ll i = 0; i < n; ++i) {
            linear.push_back(s.substr(i, n));
        }

        cout << *min_element(linear.begin(), linear.end()) << endl;
    }
}
