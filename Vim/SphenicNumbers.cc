#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    ll n;
    cin >> n;

    vb prime(n+1, true);
    for (ll i = 2; i <= n; ++i) {
        if (prime[i]) {
            for (ll j = i+i; j <= n; j += i) {
                prime[j] = false;
            }
        }
    }

    ll primes = 0;
    for (ll i = 2; i < n; ++i) {
        if (prime[i] && n % i == 0 && n % (i*i) != 0) {
            ++primes;
        }
    }

    if (primes == 3)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
