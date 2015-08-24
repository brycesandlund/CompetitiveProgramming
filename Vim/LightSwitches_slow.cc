#include <iostream>
#include <vector>
#include <set>
#include <cstdio>


using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef set<ll> si;

vi get_divisors(ll n) {
    vi divisors;
    for (ll i = 1; i*i <= n; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
        }
    }

    for (ll i = divisors.size()-1; i >= 0; --i) {
        if (divisors[i]*divisors[i] != n) {
            divisors.push_back(n / divisors[i]);
        }
    }

    return divisors;
}

int main() {
    ll N, t, b;
    for (ll cs = 1; cin >> N >> t >> b; ++cs) {
        t = t % (N+1);
        
        vi divisors = get_divisors(b);
        bool flip = false;
        for (ll i = 0; i < divisors.size(); ++i) {
            if (divisors[i] > t)
                break;
            flip = !flip;
        }
        if (flip)
            printf("Case %lld: On\n", cs);
        else
            printf("Case %lld: Off\n", cs);
    }

    return 0;
}
