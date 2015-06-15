#include <iostream>
#include <vector>

#define M 1000000007

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll powmod(ll x, ll n) {
    if (n == 1)
        return x;
    else if (n % 2 == 0) {
        ll result = powmod(x, n/2);
        return (result*result) % M;
    }
    else {
        return (x * powmod(x, n-1)) % M;
    }
}

int main() {
    ll n;
    cin >> n;
    string S;
    cin >> S;

    vi counts(26, 0);
    for (ll i = 0; i < S.size(); ++i) {
        ++counts[S[i] - 'A'];
    }

    ll n_maxes = 1;
    ll max_idx = 0;
    for (ll i = 1; i < 26; ++i) {
        if (counts[i] > counts[max_idx]) {
            n_maxes = 1;
            max_idx = i;
        }
        else if (counts[i] == counts[max_idx]) {
            ++n_maxes;
        }
    }

    //cerr << n_maxes << " " << max_idx << endl;
    cout << powmod(n_maxes, n) << endl;

    return 0;
}
