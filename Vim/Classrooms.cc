#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int main() {
    ll n, k;
    cin >> n >> k;

    vii interval(n);
    for (ll i = 0; i < n; ++i) {
        cin >> interval[i].second >> interval[i].first;
    }
    sort(interval.begin(), interval.end());

    multiset<ll> q;
    ll activities = 0;
    for (ll i = 0; i < n; ++i) {
        multiset<ll>::iterator it = q.lower_bound(interval[i].second);
        if (it != q.begin()) {
            --it;
            q.erase(it);
            q.insert(interval[i].first);
            ++activities;
        }
        else if (q.size() < k) {
            q.insert(interval[i].first);
            ++activities;
        }
    }
    cout << activities << endl;
    return 0;
}
