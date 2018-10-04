#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

#define INF 1000000000000LL

using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

map<ll, ll> count_it(vi array) {
    map<ll, ll> counts;
    for (ll i = 0; i < array.size(); ++i) {
        if (!counts.count(array[i])) {
            counts[array[i]] = 0;
        }
        ++counts[array[i]];
    }
    return counts;
}

int main() {
    ll t;
    cin >> t;
    for (ll cs = 1; cs <= t; ++cs) {
        ll n;
        cin >> n;
        vi nums(n);
        for (ll i = 0; i < n; ++i) {
            cin >> nums[i];
        }

        map<ll, ll> counts = count_it(nums);
        counts[INF] = 0;

        multiset<ll> cur_lengths;
        ll min_length = n;
        ll prev = -INF;
        for (auto it = counts.begin(); it != counts.end(); ++it) {
            vi new_vals;
            auto it2 = cur_lengths.begin();

            for (ll i = 0; i < it->second; ++i) {
                if (it2 != cur_lengths.end() && it->first == prev+1) {
                    new_vals.push_back(*it2 + 1);
                    it2 = cur_lengths.erase(it2);
                }
                else {
                    new_vals.push_back(1);
                }
            }

            if (it2 != cur_lengths.end()) {
                min_length = min(min_length, *it2);
                cur_lengths.clear();
            }

            cur_lengths.insert(new_vals.begin(), new_vals.end());
            prev = it->first;
        }

        cout << min_length << endl;
    }
}
