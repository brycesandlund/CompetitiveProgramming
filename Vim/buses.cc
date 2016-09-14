#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

int main() {
    ll a, ta, b, tb;
    cin >> a >> ta >> b >> tb;

    ll hh, mm;
    scanf("%lld:%lld", &hh, &mm);

    ll time = hh*60 + mm - 300;
    ll time_b = time-tb;
    ll time_e = time+ta;

    ll n_buses = 0;
    for (ll i = 0; i < 24*60-300; i += b) {
        if (i > time_b && i < time_e)
            ++n_buses;
    }

    cout << n_buses << endl;

    return 0;
}
