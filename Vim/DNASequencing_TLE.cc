#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<vvs> vvvs;

vs reconstruct(ll i, ll j, vvvi &parent, vvvs &memo, string &a, string &b) {
    if (!memo[i][j].empty()) {
        return memo[i][j];
    }

    if (i == 0 || j == 0) {
        return vs(1, "");
    }

    vs result;
    for (ll k = 0; k < parent[i][j].size(); ++k) {
        if (parent[i][j][k] == 0) {
            vs prev = reconstruct(i-1, j, parent, memo, a, b);
            result.insert(result.end(), prev.begin(), prev.end());
        }
        if (parent[i][j][k] == 2) {
            vs prev = reconstruct(i, j-1, parent, memo, a, b);
            result.insert(result.end(), prev.begin(), prev.end());
        }
        if (parent[i][j][k] == 1) {
            vs prev = reconstruct(i-1, j-1, parent, memo, a, b);
            for (ll l = 0; l < prev.size(); ++l) {
                result.push_back(prev[l] + a[i-1]);
            }
        }
    }

    sort(result.begin(), result.end());
    vs::iterator it = unique(result.begin(), result.end());
    result.resize(it-result.begin());

    return memo[i][j] = result;
}

int main() {
    string a, b;
    for (ll cs = 1; cin >> a >> b; ++cs) {
        ll n = a.size()+1;
        ll m = b.size()+1;
        
        vvvi parent(n, vvi(m));
        vvi bestLength(n, vi(m, 0));

        for (ll i = 1; i < n; ++i) {
            for (ll j = 1; j < m; ++j) {
                if (a[i-1] == b[j-1]) {
                    bestLength[i][j] = bestLength[i-1][j-1]+1;
                    parent[i][j] = vi(1, 1);
                }

                if (bestLength[i-1][j] > bestLength[i][j]) {
                    parent[i][j] = vi(1, 0);
                    bestLength[i][j] = bestLength[i-1][j];
                }
                else if (bestLength[i-1][j] == bestLength[i][j]) {
                    parent[i][j].push_back(0);
                }

                if (bestLength[i][j-1] > bestLength[i][j]) {
                    parent[i][j] = vi(1, 2);
                    bestLength[i][j] = bestLength[i][j-1];
                }
                else if (bestLength[i][j-1] == bestLength[i][j]) {
                    parent[i][j].push_back(2);
                }
            }
        }

        if (cs != 1)
            cout << endl;

        vvvs memo(n, vvs(m));
        vs result = reconstruct(n-1, m-1, parent, memo, a, b);
        for (ll i = 0; i < result.size(); ++i) {
            cout << result[i] << endl;
        }
    }
}
