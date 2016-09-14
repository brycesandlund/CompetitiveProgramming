#include <iostream>
#include <vector>
#include <string>

#define INF 1000000

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

    vvi sets(n);
    for (ll i = 0; i < n; ++i) {
        ll m;
        cin >> m;

        for (ll j = 0; j < m; ++j) {
            string str;
            cin >> str;

            sets[i].push_back(string_to_mask(str));
        }
    }

    vvi result(n, vi(n));
    for (ll i = 0; i < n; ++i) {
        ll mask = 1 << i;
        vi dist(n, -1);
        dist[i] = 0;

        for (ll iter = 0; true; ++iter) {
            bool change = false;
            ll new_mask = mask;
            for (ll j = 0; j < n; ++j) {
                if (dist[j] == -1) {
                    for (ll k = 0; k < sets[j].size(); ++k) {
                        if ((sets[j][k] & mask) == sets[j][k]) {
                            change = true;
                            dist[j] = iter+1;
                            new_mask = (new_mask | (1 << j));
                        }
                    }
                }
            }
            if (!change)
                break;
            mask = new_mask;
        }

        for (ll j = 0; j < n; ++j) {
            result[j][i] = dist[j];
        }
    }

    for (ll i = 0; i < n; ++i) {
        cout << result[i][0];
        for (ll j = 1; j < n; ++j) {
            cout << " " << result[i][j];
        }
        cout << endl;
    }

    return 0;
}
