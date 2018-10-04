#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef vector<ll> vi;

map<char, ll> count_it(string array) {
    map<char, ll> counts;
    for (ll i = 0; i < array.size(); ++i) {
        if (!counts.count(array[i])) {
            counts[array[i]] = 0;
        }
        ++counts[array[i]];
    }
    return counts;
}

int main() {
    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        string S;
        cin >> S;

        if (S.size() % 2 == 1) {
            cout << -1 << endl;
        }
        else {
            string S1 = S.substr(0, S.size()/2);
            string S2 = S.substr(S.size()/2);

            map<char, ll> count_A = count_it(S1);
            map<char, ll> count_B = count_it(S2);

            ll dissimilar = 0;
            for (ll i = 0; i < S1.size(); ++i) {
                if (!count_B.count(S1[i]) || count_B[S1[i]] == 0) {
                    ++dissimilar;
                }
                else {
                    --count_B[S1[i]];
                }
            }

            cout << dissimilar << endl;
        }
    }
}
