// testing for runtime test

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef vector<iii> viii;

ll find(vi &C, ll x) { return (C[x] == x) ? x : C[x] = find(C, C[x]); }

int main() {
    ll n, m;
    cin >> n >> m;
    
    vvi table(n, vi(m));
    viii nums;

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            cin >> table[i][j];
            nums.push_back(iii(table[i][j], ii(i, j)));
        }
    }

    vvi sol(n, vi(m));
    sort(nums.begin(), nums.end());

    vi max_row(n, 0);
    vi max_col(m, 0);

    for (ll i = 0; i < nums.size();) {
        ll j;
        for (j = i; nums[j].first == nums[i].first && j < nums.size(); ++j) {
        }

        vi UF(j-i);
        for (ll k = 0; k < UF.size(); ++k)
            UF[k] = k;

        vi row(n, -1), col(m, -1);
        for (ll k = i; k < j; ++k) {
            if (row[nums[k].second.first] != -1) {
                UF[find(UF, k-i)] = UF[find(UF, row[nums[k].second.first])];
            }
            if (col[nums[k].second.second] != -1) {
                UF[find(UF, k-i)] = UF[find(UF, col[nums[k].second.second])];
            }
            row[nums[k].second.first] = k-i;
            col[nums[k].second.second] = k-i;
        }

        vi max_per(j-i, 0);
        for (ll k = i; k < j; ++k) {
            max_per[find(UF, k-i)] = max(max_per[find(UF, k-i)], max_row[nums[k].second.first]);
            max_per[find(UF, k-i)] = max(max_per[find(UF, k-i)], max_col[nums[k].second.second]);
        }

        for (ll k = i; k < j; ++k) {
            ll val = max_per[find(UF, k-i)]+1;
            sol[nums[k].second.first][nums[k].second.second] = val;
            max_row[nums[k].second.first] = val;
            max_col[nums[k].second.second] = val;
        }

        i = j;
    }

    for (ll i = 0; i < n; ++i) {
        cout << sol[i][0];
        for (ll j = 1; j < m; ++j) {
            cout << " " << sol[i][j];
        }
        cout << endl;
    }

    return 0;
}
