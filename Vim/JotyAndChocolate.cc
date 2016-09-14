#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    ll n, a, b, p, q;
    cin >> n >> a >> b >> p >> q;

    if (p < q) {
        swap(p, q);
        swap(a, b);
    }

    ll red = n / a;
    ll blue = n / b - n / (a*b);

    cout << red*p + blue*q << endl;

    return 0;
}
