#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

vi solve(ll n, ll k, vi &ways) {
    if (k == 1)
        return vi(n-1, 0);
    else if (k == 2) {
        vi ans(n-1, 0);
        ans[n-2] = 1;
        return ans;
    }
    
    for (ll i = 0; i < ways.size(); ++i) {
        if (ways[i] >= k) {
            vi ans = solve(n, k-ways[i-1], ways);
            ans[n-i-2] = 1;
            return ans;
        }
    }
}

int main() {
    ll n, k;
    cin >> n >> k;

    vi ways(52);
    ways[0] = 2;
    ways[1] = 3;
    for (ll i = 2; i < ways.size(); ++i) {
        ways[i] = ways[i-1] + ways[i-2];
    }


    vi flips = solve(n, k, ways);
    vi id(n);
    for (ll i = 0; i < n; ++i) {
        id[i] = i+1;
    }

    for (ll i = 0; i < n-1; ++i) {
        if (flips[i] == 1) {
            swap(id[i], id[i+1]);
        }
    }

    cout << id[0];
    for (ll i = 1; i < n; ++i) {
        cout << " " << id[i];
    }
    cout << endl;

    return 0;
}
