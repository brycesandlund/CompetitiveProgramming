#include <iostream>
#include <vector>
#include <cstdio>

#define INF 1000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

int main() {
    vb prime(1 << 16, true);
    prime[0] = prime[1] = false;
    for (ll i = 2; i*i <= prime.size(); ++i) {
        if (prime[i]) {
            for (ll j = i+i; j < prime.size(); j += i) {
                prime[j] = false;
            }
        }
    }

    ll L, U;
    for (ll cs = 1; cin >> L >> U; ++cs) {
        vb prime_range(U-L+1, true);
        if (0 - L >= 0) {
            prime_range[0-L] = false;
        }
        if (1 - L >= 0) {
            prime_range[1-L] = false;
        }

        for (ll i = 0; i < prime.size(); ++i) {
            if (prime[i]) {
                for (ll j = max(i * ((L+i-1)/i), i+i); j <= U; j += i) {
                    prime_range[j-L] = false;
                }
            }
        }

        ll last = -1;
        ll smallest_i = -1;
        ll smallest_j = INF;
        ll largest_i = 0;
        ll largest_j = -1;
        for (ll i = 0; i < prime_range.size(); ++i) {
            if (prime_range[i]) {
                if (last != -1) {
                    if (i - last > largest_j - largest_i) {
                        largest_i = last;
                        largest_j = i;
                    }
                    if (i - last < smallest_j - smallest_i) {
                        smallest_i = last;
                        smallest_j = i;
                    }
                }
                last = i;
            }
        }

        if (smallest_i != -1) {
            printf("%lld,%lld are closest, %lld,%lld are most distant.\n", smallest_i+L, smallest_j+L, largest_i+L, largest_j+L);
        }
        else {
            cout << "There are no adjacent primes." << endl;
        }
    }

    return 0;
}
