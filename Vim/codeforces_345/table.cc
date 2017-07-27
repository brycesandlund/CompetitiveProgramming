#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int main() {
    ll n, m;
    cin >> n >> m;
    
    vvi table(n, vi(m));
    unordered_set<ll> nums_p;
    vi nums;
    unordered_map<ll, vii> num_to_pos;

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            cin >> table[i][j];

            if (nums_p.count(table[i][j]) == 0) {
                nums.push_back(table[i][j]);
                nums_p.insert(table[i][j]);
            }
            
            num_to_pos[table[i][j]].push_back(ii(i, j));
        }
    }

    vvi sol(n, vi(m));
    sort(nums.begin(), nums.end());

    vi max_row(n, 0);
    vi max_col(m, 0);

    for (ll i = 0; i < nums.size(); ++i) {
        ll max_val = 0;
        vii poses = num_to_pos[nums[i]];
        
        for (ll j = 0; j < poses.size(); ++j) {
            max_val = max(max_val, max_row[poses[j].first]);
            max_val = max(max_val, max_col[poses[j].second]);
        }

        for (ll j = 0; j < poses.size(); ++j) {
            sol[poses[j].first][poses[j].second] = max_val+1;
            max_row[poses[j].first] = max_val+1;
            max_col[poses[j].second] = max_val+1;
        }
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
