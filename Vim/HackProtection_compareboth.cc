#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

void findAnds(vi &And, vi &LastIdx, vi &nums, ll start, ll end, ll diff) {
    ll prev = nums[start];
    And.push_back(prev);
    LastIdx.push_back(start-diff);
    for (ll i = start+diff; i != end+diff; i += diff) {
        if ((nums[i] & prev) != prev) {
            LastIdx.push_back(i-diff);
            prev = nums[i] & prev;
            And.push_back(prev);
        }
    }
    LastIdx.push_back(end);
}

ll count(vi &nums, ll cur, ll start, ll end) {
    ll prev = 0;
    ll total = 0;
    for (ll i = start; i <= end; ++i) {
        prev ^= nums[i];
        if (prev == cur) ++total;
    }
    return total;
}

ll solve(vi &nums, ll start, ll end) {
    if (start == end) return 1;
    ll mid = (start+end)/2;
    ll left = solve(nums, start, mid);
    ll right = solve(nums, mid+1, end);

    vi leftAnd;
    vi leftLastIdx;
    vi rightAnd;
    vi rightLastIdx;
    findAnds(leftAnd, leftLastIdx, nums, mid, start, -1);
    findAnds(rightAnd, rightLastIdx, nums, mid+1, end, 1);

    ll total = 0;
    for (ll i = 0; i < leftAnd.size(); ++i) {
        for (ll j = 0; j < rightAnd.size(); ++j) {
            ll cur = leftAnd[i] & rightAnd[j];
            total += count(nums, cur, rightLastIdx[j]+1, rightLastIdx[j+1]);
            total += count(nums, cur, leftLastIdx[i]-1, leftLastIdx[i+1]), 
        }
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
