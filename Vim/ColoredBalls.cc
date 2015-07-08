#include <iostream>
#include <vector>

#define M 1000000007
#define MAXN 1020

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

vvi nCr(MAXN, vi(MAXN, 0));

void pop_nCr() {
    for (ll i = 0; i < MAXN; ++i) {
        nCr[i][0] = 1;
    }

    for (ll i = 1; i < MAXN; ++i) {
        for (ll j = 1; j <= i; ++j) {
            nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]) % M;
        }
    }
}

int main() {
    pop_nCr();
    ll k;
    cin >> k;
    vi c(k);
    ll total = 0;
    for (ll i = 0; i < k; ++i) {
        cin >> c[i];
        total += c[i];
    }

    ll ans = 1;
    ll prev = 0;
    for (ll i = 0; i < k; ++i) {
        ans = (ans * (nCr[prev+c[i]-1][c[i]-1])) % M;
        prev += c[i];
    }

    cout << ans << endl;

    return 0;
}
