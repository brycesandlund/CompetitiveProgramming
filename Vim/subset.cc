#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

bool is_prime(ll n) {
    for (ll i = 2; i*i <= n; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main() {
    ll n;
    cin >> n;
    vi a(n);
    
    ll n1s = 0;
    ll pm1 = -1;
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] == 1)
            ++n1s;
        
        if (pm1 == -1 && is_prime(a[i]+1) && a[i] != 1)
            pm1 = a[i];
    }

    if (n1s >= 2) {
        cout << (n1s + (pm1 == -1 ? 0 : 1)) << endl;
        if (pm1 != -1)
            cout << pm1 << " ";
        
        for (ll i = 0; i < n1s-1; ++i) {
            cout << 1 << " ";
        }
        cout << 1 << endl;
    }
    else {
        for (ll i = 0; i < n; ++i) {
            for (ll j = i+1; j < n; ++j) {
                if (is_prime(a[i] + a[j])) {
                    cout << 2 << endl;
                    cout << a[i] << " " << a[j] << endl;
                    goto END;
                }
            }
        }
        cout << 1 << endl;
        cout << a[0] << endl;
    }
END:
    return 0;
}
