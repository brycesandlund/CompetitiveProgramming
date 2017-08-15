#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <iomanip>
#include <set>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

int main() {
    vvi p_factors(1000010);
    vb prime(1000010, true);
    for (ll i = 2; i < 1000010; ++i) {
        if (prime[i]) {
            for (ll j = i; j < 1000010; j += i) {
                prime[j] = false;

                for (ll cp = j; cp % i == 0; cp /= i) {
                    p_factors[j].push_back(i);
                }
            }
        }
    }

    ll n;
    cin >> n;

    map<ll, ll> num_gcd;
    vi a(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
        set<ll> factors(p_factors[a[i]].begin(), p_factors[a[i]].end());
        vi factors_c;
        for (auto it = factors.begin(); it != factors.end(); ++it) {
            factors_c.push_back(0);
            for (ll cp = a[i]; cp % (*it) == 0; cp /= (*it)) {
                factors_c.back()++;
            }
        }

    }
}
