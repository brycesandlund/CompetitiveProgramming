#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef pair<ii, ll> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;

int main() {
    ll n, m;
    cin >> n >> m;
    vi l(n), r(n);
    for (ll i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
    }

    viii gaps(n-1);
    for (ll i = 0; i < n-1; ++i) {
        gaps[i] = iii(ii(r[i+1] - l[i], l[i+1] - r[i]), i);
    }

    sort(gaps.begin(), gaps.end());

    set<ii> bridges;
    for (ll i = 0; i < m; ++i) {
        ll val;
        cin >> val;
        bridges.insert(ii(val, i));
    }

    bool success = true;
    vi sol(n-1);
    for (ll i = 0; i < n-1; ++i) {
        set<ii>::iterator it = bridges.lower_bound(ii(gaps[i].first.second, -1));
        if (it == bridges.end()) {
            success = false;
            break;
        }
        else if (it->first > gaps[i].first.first) {
            success = false;
            break;
        }
        else {
            sol[gaps[i].second] = it->second;
            bridges.erase(it);
        }
    }

    if (success) {
        cout << "Yes" << endl;
        cout << sol[0]+1;
        
        for (ll i = 1; i < n-1; ++i) {
            cout << " " << sol[i]+1;
        }
        cout << endl;
    }
    else {
        cout << "No" << endl;
    }
    return 0;
}
