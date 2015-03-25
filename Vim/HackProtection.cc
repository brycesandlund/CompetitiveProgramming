#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll solve(vi &nums, ll start, ll end) {
    if (start == end) return 1;
    ll mid = (start+end)/2;
    ll left = solve(nums, start, mid);
    ll right = solve(nums, mid+1, end);

    ll prevXOR = 0;
    ll prevAND = nums[mid];
    map<ll, ll> leftXORs;
    ll total = 0;
    for (ll i = mid; true; --i) {
        if (i == start-1 || (nums[i] & prevAND) != prevAND) {
            ll curAND = prevAND;
            ll curXOR = 0;
            for (ll j = mid+1; j <= end; ++j) {
                curAND &= nums[j];
                curXOR ^= nums[j];
                ll x = curAND ^ curXOR;
                if (leftXORs.count(x)) {
                    total += leftXORs[x];
                }
            }

            prevAND = nums[i] & prevAND;
            leftXORs.clear();
        }
        if (i == start-1) break;
        prevXOR ^= nums[i];
        if (!leftXORs.count(prevXOR)) {
            leftXORs[prevXOR] = 0;
        }
        ++leftXORs[prevXOR];
    }

    return total + left + right;
}

int main() {
    ll n;
    for (ll cs = 1; cin >> n; ++cs) {
        vi a(n);
        for (ll i = 0; i < n; ++i) {
            cin >> a[i];
        }

        cout << solve(a, 0, n-1) << endl;
    }
}
