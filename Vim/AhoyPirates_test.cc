#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

int main() {
    ll nTests = 100;
    cout << nTests << endl;
    for (ll cs = 1; cs <= nTests; ++cs) {
        //ll M = rand()%99+1, T = rand()%199+1, Q = rand()%999+1, L = rand()%49+1;
        ll M = 100, T = 200, Q = 1000, L = 50;
        cout << M << endl;
        for (ll i = 0; i < M; ++i) {
            cout << T << endl;
            for (ll k = 0; k < L; ++k) {
                cout << rand()%2;
            }
            cout << endl;
        }

        cout << Q << endl;
        for (ll i = 0; i < Q; ++i) {
            ll r = rand()%4;
            ll a = rand()%(M*T*L), b = rand()%(M*T*L);
            if (a > b) swap(a, b);
            if (r == 0)
                cout << "F";
            else if (r == 1)
                cout << "E";
            else if (r == 2)
                cout << "I";
            else
                cout << "S";

            cout << " " << a << " " << b << endl;
        }
    }
}
