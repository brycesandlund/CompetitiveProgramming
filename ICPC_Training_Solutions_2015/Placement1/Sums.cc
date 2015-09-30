#include <iostream>

#define INF 1000000000000LL

using namespace std;

typedef long long ll;

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll N;
        cin >> N;

        ll min_k = INF;
        for (ll i = 2; i*i <= 2*N; ++i) {
            if (2*N % i == 0) {
                if (i % 2 == 1 || (2*N/i) % 2 == 1) {
                    min_k = min(i, min_k);
                //    break;
                }
            }
        }

        if (min_k == INF) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            ll n = (2*N/min_k - min_k+1)/2;
            cout << N << " = " << n;
            for (ll i = 1; i < min_k; ++i) {
                cout << " + " << n+i;
            }
            cout << endl;
        }
    }
    return 0;
}
