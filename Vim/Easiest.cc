#include <iostream>

using namespace std;

typedef long long ll;

ll digit_sum(ll x) {
    ll count = 0;
    while (x) {
        count += x % 10;
        x /= 10;
    }
    return count;
}

int main() {
    ll N;
    for (ll cs = 1; cin >> N && N; ++cs) {
        for (ll q = 11; ; ++q) {
            if (digit_sum(N) == digit_sum(N*q)) {
                cout << q << endl;
                break;
            }
        }
    }
}
