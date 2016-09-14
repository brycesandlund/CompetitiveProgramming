#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    ll n, a, b, c;
    cin >> n >> a >> b >> c;

    if (a <= (b-c) || b > n) {
        cout << (n / a) << endl;
    }
    else {
        n -= b;

        ll ans = n / (b-c);
        n -= ans * (b-c);
        ans += 1;
        n += c;

        ans += n / a;
        cout << ans << endl;
    }

    return 0;
}
