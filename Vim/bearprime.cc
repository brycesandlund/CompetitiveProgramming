#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

int main() {
    ll small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

    bool prime = true;
    ll multiplier = 1;

    for (ll i = 0; i < 16;) {
        if (small_primes[i]*multiplier > 100)
            break;

        cout << small_primes[i]*multiplier << endl;
        fflush(stdout);

        string ans;
        cin >> ans;

        if (ans == "yes") {
            if (multiplier != 1) {
                cout << "composite" << endl;
                return 0;
            }
            multiplier *= small_primes[i];
        }
        else {
            ++i;
        }
    }

    cout << "prime" << endl;
}
