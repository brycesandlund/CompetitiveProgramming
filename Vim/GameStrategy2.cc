#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

ll string_to_mask(string str) {
    ll mask = 0;
    for (ll i = 0; i < 26; ++i) {
        if (str.find('a'+i) != string::npos) {
            mask = mask | (1 << i);
        }
    }
    return mask;
}

int main() {
    ll n;
    cin >> n;

    vvi mask_to_pos(1 << n);
    for (ll i = 0; i < n; ++i) {
        ll m;
        cin >> m;

        for (ll j = 0; j < m; ++j) {
            string str;
            cin >> str;

            mask_to_pos[string_to_mask(str)].push_back(i);
        }
    }

    vvi adj_list(1 << n);

    return 0;
}
