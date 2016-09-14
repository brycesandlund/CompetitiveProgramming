#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    ll n;
    cin >> n;

    ll A = 1234567;
    ll B = 123456;
    ll C = 1234;

    bool works = false;
    for (ll a = 0; a*A <= n; ++a) {
        for (ll b = 0; a*A + b*B <= n; ++b) {
            if ((n - (a*A + b*B)) % C == 0) {
                works = true;
            }
        }
    }

    if (works)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
