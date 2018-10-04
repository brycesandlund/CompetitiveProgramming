#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <functional>

#define INF 1000000000000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int main() {
    ll N, K;
    cin >> N >> K;

    vi A(N);
    multiset<ll> nums;
    for (ll i = 0; i < N; ++i) {
        cin >> A[i];
        nums.insert(A[i]);
    }

    sort(A.begin(), A.end());
    
    priority_queue<ii, vii, greater<ii> > gaps;
    for (ll i = 0; true; ++i) {
        if (i+K-1 >= N) break;
        gaps.push(ii(A[i+K-1] - A[i], i));
    }

    ll max_gap = 0;
    while (!nums.empty()) {
        max_gap = gaps.top().first;
        ll start = gaps.top().second; 
        gaps.pop();

        while (true) {
            auto it = nums.lower_bound(A[start]);
            if (it == nums.end() || *it > A[start]+max_gap)
                break;
            nums.erase(it);
        }
    }

    cout << max_gap << endl;
}
