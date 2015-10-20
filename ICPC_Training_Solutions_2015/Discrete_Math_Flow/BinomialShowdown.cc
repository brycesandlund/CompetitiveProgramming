#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef unordered_map<ll, ll> mii;
typedef unordered_map<ll, mii> mmii;

mmii memo;

ll nCr(ll n, ll r) {
    if (r > n/2) {
        return nCr(n, n-r);
    }

    if (r == 0) {
        return 1;
    }

    if (r == 1) {
        return n;
    }

    if (memo.count(n) && memo[n].count(r)) {
        return memo[n][r];
    }

   return memo[n][r] = nCr(n-1, r-1) + nCr(n-1, r);
}

int main() {
    ll n, k;
    for (ll cs = 1; cin >> n >> k && n; ++cs) {
        cout << nCr(n, k) << endl;
    }
    return 0;
}
