#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

typedef long long ll;

int main() {
    ll n = 10000;
    ll q = n;
    cout << n << " " << q << endl;
    for (ll i = 0; i < n; ++i) {
        cout << rand()%1000000 << " " << rand()% 1000000;
    }

    for (ll i = 0; i < q; ++i) {
        ll one = rand()%(n-1)+1;
        ll two = rand()%(n-1)+1;

        cout << min(one, two) << " " << max(one, two)+1 << endl;
    }
}
