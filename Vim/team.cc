#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

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

        ll lo = 0;
        ll hi = n;

        while (lo+1 < hi) {
            map<ll, ll> counts_2 = counts;
            ll mid = (lo + hi) / 2;

            bool success = true;
            map<ll, ll> end_counts;

            while (counts_2.size() != 0) {
                auto it = counts_2.begin();
                ll start = it->first;
                bool last = false;

                for (ll i = 0; i < mid; ++i) {
                    if (last || i + start != it->first) {
                        if (end_counts.count(start-1)) {
                            end_counts[start-1]--;

                            if (end_counts[start-1] == 0) {
                                end_counts.erase(start-1);
                            }
                        }
                        else {
                            success = false;
                            goto END;
                        }
                    }
                    --it->second;
                    if (it->second == 0) {
                        it = counts_2.erase(it);
                    }
                    else {
                        ++it;
                    }

                    if (it == counts_2.end()) {
                        last = true;
                    }
                }

                if (!end_counts.count(start+mid-1)) {
                    end_counts[start+mid-1] = 0;
                }

                ++end_counts[start+mid-1];
            }
END:
            if (success) {
                lo = mid;
            }
            else {
                hi = mid;
            }
        }

        cout << lo << endl;
    }
}
