#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;


int main() {
    ll n;
    for (ll cs = 1; cin >> n; ++cs) {
        ll nCool = 0;
        for (ll i = 0; i < n; ++i) {
            string word;
            cin >> word;

            vi counts(26, 0);
            for (ll j = 0; j < (ll)word.size(); ++j) {
                ++counts[word[j] - 'a'];
            }

            vi countsList;
            for (ll i = 0; i < 26; ++i) {
                if (counts[i] != 0) {
                    countsList.push_back(counts[i]);
                }
            }

            sort(countsList.begin(), countsList.end());
            bool success = countsList.size() > 1;
            for (ll i = 1; i < (ll)countsList.size(); ++i) {
                if (countsList[i] == countsList[i-1]) {
                    success = false;
                }
            }

            if (success) {
                ++nCool;
            }
        }

        printf("Case %lld: %lld\n", cs, nCool);
    }
}
